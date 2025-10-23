/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:54:09 by gorg              #+#    #+#             */
/*   Updated: 2024/05/03 18:00:09 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	i;

	i = !n;
	if (n < 0)
		i++;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static char	*itoa(int n, int i, char *p)
{
	p[0] = '-';
	while (i != 1)
	{
		p[i - 1] = '0' - (n % 10);
		n /= 10;
		i--;
	}
	return (p);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		i;

	i = ft_intlen(n);
	p = malloc(sizeof(char) * i + 1);
	if (!p)
		return (NULL);
	p[i] = '\0';
	if (n >= 0)
	{
		while (i != 0)
		{
			p[--i] = '0' + (n % 10);
			n /= 10;
		}
	}
	else
		p = itoa(n, i, p);
	return (p);
}
