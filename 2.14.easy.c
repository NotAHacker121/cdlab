#include <stdio.h>
#include <ctype.h>
#include <string.h>
char g[50][50], f[50];
int numOfProds, m = 0;

int first(char ch)
{
    int flag = 0;
    if (islower(ch))
    {
        f[m++] = ch;
        return 0;
    }
    else
    {
        for (int k = 0; k < numOfProds; k++)
        {
            if (g[k][0] == ch)
            {
                if (g[k][2] == 'e')
                    flag = 1;
                else if (islower(g[k][2]))
                    f[m++] = g[k][2];
                else
                {
                    int temp = 1;
                    int x = 0;
                    while (temp == 1 && (2 + x) < strlen(g[k]))
                    {
                        temp = first(g[k][2 + x]);
                        x++;
                    }
                    if ((2 + x) == strlen(g[k]) && temp == 1)
                        flag = 1;
                }
            }
        }
        return flag;
    }
}
void follow(char ch)
{
    if (ch == g[0][0])
        f[m++] = 'e';
    for (int k = 0; k < numOfProds; k++)
    {
        for (int j = 2; j < strlen(g[k]); j++)
        {
            if (g[k][j] == ch && (j + 1) == strlen(g[k]) && g[k][0] != ch)
                follow(g[k][0]);
            else if (g[k][j] == ch)
            {
                int temp = 1, x = 1;
                while (temp == 1 && (j + x) < strlen(g[k]))
                {
                    temp = first(g[k][j + x]);
                    x++;
                }
                if ((j + x) == strlen(g[k]) && temp == 1 && g[k][0] != ch)
                    follow(g[k][0]);
            }
        }
    }
}

void main()
{
    int ch;
    char input;
    printf("Enter the number of productions : ");
    scanf("%d", &numOfProds);
    for (int i = 0; i < numOfProds; i++)
        scanf("%s%c", g[i], &input);
    do
    {
        printf("Enter the terminal you want to find first and follow for :");
        scanf("%c", &input);
        strcpy(f, " ");
        int temp = first(input);
        printf("First(%c)={", input);
        for (int i = 0; i < m; i++)
            printf("%c ", f[i]);
        if (temp == 1)
            printf("e");
        printf("}\n");
        strcpy(f, " ");
        m = 0;
        follow(input);
        printf("Follow(%c)={", input);
        for (int i = 0; i < m; i++)
            printf("%c ", f[i]);
        printf("}\n");
        printf("Do you want to continue (1||0) :");
        scanf("%d%c", &ch, &input);
    } while (ch == 1);
}