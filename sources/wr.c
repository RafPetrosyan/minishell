void    write_dollar()
{
    printf("$");
}

void    write_non_quote(char *str, int *i, char *str1, int *j)
{
    while (str[*i] != '\0')
    {  
        if (str[*i] == ' ' || str[*i] == '\0' || str[*i] == '\'' || str[*i] == '"')
            return ;
        if (str[*i] == '$')
            write_dollar();
        else
            str1[*j] = str[*i];
        ++(*i);
        ++(*j);

    }
}

void write_one_quote(char *str, int *i, char *str1, int *j)
{
    int flag;

    flag = 0;
    while (str[*i] != '\0')
    {
        if (str[*i] == '\'')
        {
            ++flag;
            ++(*i);
            continue;
        }
        if (flag == 2)
            return ;
        str1[*j] = str[*i];
        ++(*i);
        ++(*j);
    }
}


void write_two_quote(char *str, int *i, char *str1, int *j)
{
    int flag;

    flag = 0;
    while (str[*i] != '\0')
    {
        if (str[*i] == '"')
        {
            ++(*i);
            ++flag;
            continue;
        }
        if (flag == 2)
            return ;
        if (str[*i] == '$')
            write_dollar();
        else
            str1[*j] = str[*i];
        ++(*i);
        ++(*j);
    }
}

void    write_tokens(char *str, int *i, char *str1, int arr_i)
{
    int    j;

    j = 0;
    while (str[*i] != '\0' && str[*i] == ' ')
        ++(*i);
    while (str[*i] != '\0')
    {
        if (str[*i] == '\'')
            write_one_quote(str, i, str1, &j);
        else if (str[*i] == '"')
            write_two_quote(str, i, str1, &j);
        else
            write_non_quote(str, i, str1, &j);
        if (str[*i] == ' ')
            break ;
    }
    str1[j] = '\0';
}

#include <stdlib.h>

int main() {
  int i=0;
  char str[] = "hello'a'\"c\"a";
  char *str1 = malloc(11 * sizeof(char));
  write_tokens(str, &i,str1, 10);
  return 0;
}