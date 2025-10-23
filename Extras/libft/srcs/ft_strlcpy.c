/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:54:08 by gorg              #+#    #+#             */
/*   Updated: 2024/05/05 18:58:00 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = ft_strlen(src);
	if (dstsize == 0)
		return (i);
	if (dstsize > 0)
	{
		while (*src != '\0' && dstsize-- > 1)
		{
			*dst++ = *src++;
		}
	}
	*dst = 0;
	return (i);
}
