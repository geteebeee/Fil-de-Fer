/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:31:26 by gorg              #+#    #+#             */
/*   Updated: 2024/09/17 18:02:04 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_validcheck(char c, int base)
{
	if (base <= 10 && c >= '0' && c < '0' + base)
		return (c >= '0' && c < '0' + base);
	else if ((c >= '0' && c <= '9') || (c >= 'A' && c < 'A' + base - 10)
		|| (c >= 'a' && c < 'a' + base - 10))
		return (1);
	return (0);
}

static int	ft_chartval(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	else if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	return (0);
}

static int	ft_running(int s, int base, const char *str)
{
	long	res;

	res = 0;
	while (ft_validcheck(*str, base))
	{
		if (LONG_MAX / base < res || (LONG_MAX / base == res
				&& ft_chartval(*str) > LONG_MAX % base))
		{
			if (s == -1)
				return (0);
			else
				return (-1);
		}
		res = res * base + ft_chartval(*str++);
	}
	return (res * s);
}

int	ft_atoi_base(const char *str, int base)
{
	int		sign;

	sign = 1;
	if (!(base >= 2 && base <= 16))
		return (0);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	if (base == 16 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		str += 2;
	else if (base == 2 && str[0] == '0' && (str[1] == 'b' || str[1] == 'B'))
		str += 2;
	else if (base == 8 && str[0] == '0')
		str++;
	while (*str == '0')
		str++;
	return (ft_running(sign, base, str));
}
