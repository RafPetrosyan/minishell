#include "minishell.h"

int main()
{
	char	*str;

	while (1)
	{
		str = readline("\033[38;5;43mMinishell:\033[0;000m ");
		add_history(str);
		if (check_quote(str) == 1)
			printf("%d\n", ft_get_word_count(str, ' '));
		free(str);
	}
	return (0);
}