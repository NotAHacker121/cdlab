#include <stdio.h>
#include <string.h>

int z, i, j, lenofinput;
char input[16], ac[20], stk[15], act[10];
void check();

int main()
{
  puts("GRAMMAR is E->E+E \n E->E*E \n E->(E) \n E->id");
  puts("Enter input string ");
  scanf("%s", input);
  lenofinput = strlen(input);
  strcpy(act, "SHIFT->");
  puts("stack \t input \t action");
  for (i = 0, j = 0; j < lenofinput; i++, j++)
  {
    if (input[j] == 'i' && input[j + 1] == 'd')
    {
      stk[i] = input[j];
      stk[i + 1] = input[j + 1];
      stk[i + 2] = '\0';
      input[j] = ' ';
      input[j + 1] = ' ';
      printf("\n$%s\t%s$\t%sid", stk, input, act);
      check();
    }
    else
    {
      stk[i] = input[j];
      stk[i + 1] = '\0';
      input[j] = ' ';
      printf("\n$%s\t%s$\t%ssymbols", stk, input, act);
      check();
    }
  }
  printf("\n");
}

void check()
{
  strcpy(ac, "REDUCE TO E");
  for (z = 0; z < lenofinput; z++)
    if (stk[z] == 'i' && stk[z + 1] == 'd')
    {
      stk[z] = 'E';
      stk[z + 1] = '\0';
      printf("\n$%s\t%s$\t%s", stk, input, ac);
      j++;
    }
  for (z = 0; z < lenofinput; z++)
    if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E')
    {
      stk[z] = 'E';
      stk[z + 1] = '\0';
      stk[z + 2] = '\0';
      printf("\n$%s\t%s$\t%s", stk, input, ac);
      i = i - 2;
    }
  for (z = 0; z < lenofinput; z++)
    if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E')
    {
      stk[z] = 'E';
      stk[z + 1] = '\0';
      stk[z + 2] = '\0';
      printf("\n$%s\t%s$\t%s", stk, input, ac);
      i = i - 2;
    }
  for (z = 0; z < lenofinput; z++)
    if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')')
    {
      stk[z] = 'E';
      stk[z + 1] = '\0';
      stk[z + 2] = '\0';
      printf("\n$%s\t%s$\t%s", stk, input, ac);
      i = i - 2;
    }
}