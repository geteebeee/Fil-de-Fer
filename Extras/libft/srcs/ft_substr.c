/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:18:49 by gorg              #+#    #+#             */
/*   Updated: 2024/05/05 18:59:34 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ss;
	char	*pss;
	size_t	i;

	i = ft_strlen(s);
	if (!s)
		return (0);
	if (start > i)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	ss = malloc(sizeof(char) * (len + 1));
	if (!ss)
		return (NULL);
	pss = ss;
	while (s[start] != 0 && len-- > 0)
	{
		*ss = s[start];
		ss++;
		start++;
	}
	*ss = '\0';
	return (pss);
}
