/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:23:40 by gorg              #+#    #+#             */
/*   Updated: 2024/05/05 18:59:23 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ps1;
	char	*ps2;
	char	*ps3;

	ps1 = (char *)s1;
	while (*ps1 && ft_strchr(set, *ps1))
		ps1++;
	ps2 = (char *)s1 + ft_strlen(s1) - 1;
	while (ps2 > ps1 && ft_strchr(set, *ps2))
		ps2--;
	ps3 = malloc(sizeof(char) * (ps2 - ps1 + 2));
	if (!ps3)
		return (NULL);
	ft_strlcpy(ps3, ps1, (ps2 - ps1 + 2));
	ps3[ps2 - ps1 + 1] = '\0';
	return (ps3);
}
