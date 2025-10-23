/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:17:15 by gorg              #+#    #+#             */
/*   Updated: 2024/05/05 18:56:41 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_freeer(char **dst, int i)
{
	int	j;

	j = 0;
	while (i > j)
	{
		free(dst[j]);
		j++;
	}
	free(dst);
	return (0);
}

size_t	ft_wlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s != c)
	{
		i++;
		s++;
	}
	return (i);
}

static int	ft_splchr(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s == c)
		s++;
	while (*s)
	{
		while (*s != c && *s)
			s++;
		if (*s == c)
		{
			while (*s == c && *s)
				s++;
		}
		i++;
	}
	return (i);
}

static char	**split(char const *s, char c, char **dst, size_t nr)
{
	size_t	i;
	char	**ptr;

	i = 0;
	ptr = dst;
	while (nr > i)
	{
		while (*s == c && *s)
			s++;
		if (*s == 0)
			break ;
		*dst = ft_substr(s, 0, ft_wlen(s, c));
		if (!*dst)
		{
			ft_freeer(ptr, i);
			return (NULL);
		}
		while (*s && *s != c)
			s++;
		dst++;
		i++;
	}
	*dst = 0;
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	size_t	i;
	char	**pdst;

	if (!s)
		return (NULL);
	i = ft_splchr(s, c);
	dst = malloc(sizeof(char *) * (i + 1));
	if (!dst)
		return (NULL);
	pdst = dst;
	dst = split(s, c, dst, i);
	if (!dst)
	{
		return (NULL);
	}
	return (pdst);
}
