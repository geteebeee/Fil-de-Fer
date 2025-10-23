/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:31:26 by gorg              #+#    #+#             */
/*   Updated: 2024/10/15 19:14:13 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_running(int s, const char *str)
{
	long	res;

	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		if ((LONG_MAX / 10 < res) || ((LONG_MAX / 10 == res)
				&& ((*str - '0') > LONG_MAX % 10)))
		{
			if (s == -1)
				return (0);
			else
				return (-1);
		}
		res = res * 10 + (*str++ - '0');
	}
	return (res * s);
}

int	ft_atoi(const char *str)
{
	int		s;

	s = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s *= -1;
		str++;
	}
	while (*str == '0')
		str++;
	return (ft_running(s, str));
}
