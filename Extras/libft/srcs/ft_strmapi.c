/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:55:02 by gorg              #+#    #+#             */
/*   Updated: 2024/04/27 14:02:48 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	n;
	char	*p;
	char	*pp;

	n = ft_strlen(s);
	p = malloc(sizeof(char) * n + 1);
	if (!p || !s || !f)
		return (NULL);
	pp = p;
	n = 0;
	while (*s)
	{
		*p++ = f(n++, *s++);
	}
	*p = '\0';
	return (pp);
}
