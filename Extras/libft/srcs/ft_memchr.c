/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:27:59 by gorg              #+#    #+#             */
/*   Updated: 2024/05/05 19:02:23 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ps;
	unsigned char		uc;

	uc = (unsigned char)c;
	ps = (const unsigned char *)s;
	while (n > 0)
	{
		if (*ps == uc)
			return ((void *)ps);
		ps++;
		n--;
	}
	return (0);
}
