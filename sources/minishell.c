#include "minishell.h"
# include <readline/readline.h>
int main()
{
	char	*str;

	while (1)
	{
		str = readline("Welcome my Minishell: ");
		free(str);
	}
	printf("%s", str);
}