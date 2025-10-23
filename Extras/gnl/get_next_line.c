/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:34:46 by gorg              #+#    #+#             */
/*   Updated: 2024/11/14 17:37:20 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_fetch_and_resetpt2(char **content, int len)
{
	char	*temp;

	if ((*content)[len])
	{
		temp = ft_strdup(*content + len);
		if (!*temp)
			return (NULL);
	}
	else
		temp = NULL;
	return (temp);
}

static char	*ft_fetch_and_reset(char **content)
{
	int		len;
	char	*line;
	char	*temp;

	len = 0;
	if (!content || !*content)
		return (NULL);
	while ((*content)[len] && (*content)[len] != '\n')
		len++;
	if ((*content)[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, *content, len + 1);
	temp = *content;
	*content = ft_fetch_and_resetpt2(content, len);
	if (*content == NULL && temp[len])
	{
		free(line);
		return (NULL);
	}
	free(temp);
	return (line);
}

static int	ft_reader(int fd, char *buffer, char **content)
{
	char	*temp;
	int		reader;

	temp = NULL;
	reader = read(fd, buffer, BUFFER_SIZE);
	while (reader > 0)
	{
		buffer[reader] = '\0';
		temp = *content;
		*content = ft_strjoin(temp, buffer);
		free(temp);
		if (!*content)
			return (-1);
		if (ft_strchr(*content, '\n'))
			break ;
		reader = read(fd, buffer, BUFFER_SIZE);
	}
	return (reader);
}

static char	*ft_read(int fd, char **content)
{
	char	*buffer;
	int		reader;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(*content);
		*content = NULL;
		return (NULL);
	}
	reader = ft_reader(fd, buffer, content);
	free(buffer);
	if (reader < 0 && !*content)
		return (NULL);
	return (ft_fetch_and_reset(content));
}

char	*get_next_line(int fd)
{
	static char	*content[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024 || BUFFER_SIZE > INT_MAX)
	{
		if (content[fd])
		{
			free(content[fd]);
			content[fd] = NULL;
		}
		return (NULL);
	}
	line = ft_read(fd, &content[fd]);
	if (!line)
	{
		if (content[fd])
		{
			free(content[fd]);
			content[fd] = NULL;
		}
		return (NULL);
	}
	return (line);
}
