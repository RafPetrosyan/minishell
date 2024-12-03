#include "minishell.h"

void	ft_adddig(char *str, int number, int digits)
{
	int	i;

	i = 0;
	str[digits] = '\0';
	if (number < 0)
	{
		str[i++] = '-';
		number *= -1;
	}
	while (i < digits)
	{
		str[digits - 1] = number % 10 + '0';
		--digits;
		number /= 10;
	}
}

char	*ft_itoa(int n)
{
	int		digit;
	char	*str;
	int		temp;

	digit = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		++digit;
	temp = n;
	while (temp / 10 != 0)
	{
		temp /= 10;
		++digit;
	}
	str = (char *)malloc((digit + 1) * sizeof(char));
	if (str == 0)
		return (0);
	ft_adddig(str, n, digit);
	return (str);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	numb;

	i = 0;
	sign = 1;
	numb = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		++i;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= (-1);
		++i;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		numb = numb * 10 + nptr[i] - '0';
		++i;
	}
	return (sign * numb);
}
