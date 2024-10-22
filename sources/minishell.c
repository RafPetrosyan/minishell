#include "minishell.h"

int main()
{
	char	*str;

	while (1)
	{
		str = readline("\033[38;5;43mMinishell:\033[0;000m ");
		add_history(str);
		printf("%d\n", check_quote(str));
		free(str);
	}
	return (0);
}