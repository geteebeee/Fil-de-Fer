/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:56:24 by gorg              #+#    #+#             */
/*   Updated: 2024/09/16 20:20:37 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (size && count && SIZE_MAX / size < count)
		return (NULL);
	p = malloc(count * size);
	if (!p)
		return (0);
	ft_bzero(p, size * count);
	return (p);
}
