#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int n, m = 0, p;
char a[20][20], f[20];
void follow(char c);
void first(char c);
int count = 0, flag=0;

char letter;
int main()
{

    int i, z;
    char ch;
    // clrscr();
    printf("Enter the no of prooductions:\n");
    scanf("%d", &n);
    printf("Enter the productions:\n");
    for (int i = 0; i < n; i++)
        scanf("%s%c", a[i], &ch);
    do
    {
        m = 0;
        printf("Enter the elemets whose fisrt & follow is to be found:");
        scanf("%c", &letter);
        first(letter);
        printf("First(%c)={", letter);
        for (i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");
        strcpy(f, " ");
        // flushall();
        m = 0;
        follow(letter);
        printf("Follow(%c)={", letter);
        for (i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");
        printf("Continue(0/1)?");
        scanf("%d%c", &z, &ch);
    } while (z == 1);
    return (0);
}
void first(char c)
{
    if (!isupper(c))
        f[m++] = c;
    for (int k = 0; k < n; k++)
    {
        if (a[k][0] == c)
        {
            for (int j = 2; j < strlen(a[k]); j++)
            {
                if (a[k][j] == '$')
                {
                    if (a[k][0] == letter)
                    {
                        f[m++] = '$';
                    }
                    else
                    {
                        count++;
                        continue;
                    }
                    break;
                }
                if (islower(a[k][j]))
                {
                    f[m++] = a[k][j];
                    return;
                }
                first(a[k][j]);
            }
            if (count == strlen(a[k]) - 2)
            {
                for (int p = 0; p < strlen(f); p++)
                {
                    if (f[p] == '$')
                    {
                        goto skip;
                    }
                }
                f[m++] = '$';
            skip:
                count = 0;
            }
        }
    }
}

void follow(char c)
{
    if (a[0][0] == c)
        f[m++] = '$';
    for (int i = 0; i < n; i++)
    {
        for (int j = 2; j < strlen(a[i]); j++)
        {
            if (a[i][j] == c)
            {
                for (int k = j + 1; k < strlen(a[i]); k++)
                {
                    if (a[i][k] != '\0')
                    {
                        first(a[i][k]);
                        flag=0;
                        for (int p = 0; p < strlen(f); p++)
                        {
                            if (f[p] == '$')
                            {
                                f[p] = ' ';
                                flag = 1;
                                if (k==strlen(a[i])-1){
                                    follow(a[i][0]);
                                }
                                break;
                            }
                        }
                        if (flag == 0)
                        {
                            break;
                        }
                    }
                }

                if (a[i][j + 1] == '\0' && c != a[i][0])
                    follow(a[i][0]);
            }
        }
    }
}