#include "minishell.h"

static int	ft_putchar(char c)
{
	write(2, &c, 1);
	return (1);
}

static int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (s == 0)
	{
		write(2, "(null)", 6);
		return (6);
	}
	while (s[i] != '\0')
	{
		write(2, &s[i], 1);
		++i;
	}
	return (i);
}

static int	call_specifier(char c, va_list *list)
{
	if (c == 'c')
		return (ft_putchar((char)va_arg(*list, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(*list, char *)));
	else if (c != '\0')
		return (ft_putchar(c));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	list;

	i = 0;
	count = 0;
	va_start(list, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			count += call_specifier(format[++i], &list);
			if (format[i] != '\0')
				++i;
		}
		else
		{
			write(2, &format[i++], 1);
			++count;
		}
	}
	return (count);
}
