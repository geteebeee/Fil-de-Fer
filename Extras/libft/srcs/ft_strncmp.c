/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:18:36 by gorg              #+#    #+#             */
/*   Updated: 2024/05/05 18:58:35 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (n > ft_strlen(s1) || n > ft_strlen(s2))
	{
		if (ft_strlen(s1) > ft_strlen(s2))
			n = ft_strlen(s1);
		else
			n = ft_strlen(s2);
	}
	while (n > i && s1[i] == s2[i] && *s1)
	{
		if (n - 1 == i)
			return (0);
		i++;
	}
	if ((unsigned char)s1[i] > (unsigned char)s2[i])
		return (1);
	else if ((unsigned char)s1[i] < (unsigned char)s2[i])
		return (-1);
	return (0);
}
