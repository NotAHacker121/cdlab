#include <stdio.h>
#include <stdlib.h>

int mat[20][20], n, c, r, buffer[20];

int ans[10]={100,100,100,100,100,100,100,100,100,100};
void calc(int x)
{
    int i;
    if (buffer[x])
        return;
    ans[c++] = x;
    buffer[x] = 1;
    for (i = 0; i <= n; i++)
        if (mat[x][i])
            calc(i);
}
void main()
{
    int i, j;
    char s;
    FILE *fp;
    fp = fopen("in.txt", "r");
    printf("Enter number of transitions:\n");
    scanf("%d", &n);
    printf("\ntotal number of transitions is %d", n);
    printf("\n the transitions are\n");
    while (!feof(fp))
    {
        fscanf(fp, "%d %c %d", &r, &s, &c);
        printf("\n%d %c %d", r, s, c);
        if (s == 'e')
            mat[r][c] = 1;
    }
    c = 0;
    printf("\n for which state you need e-closure?");
    scanf("%d", &i);
    calc(i);
    printf("e-closure of state %d is {", i);

    for (i = 0; ans[i]!=100; i++)
    {
        printf("%d, ", ans[i]);
    }
    printf("}");
    fclose(fp);
}