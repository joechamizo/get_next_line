/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:38:25 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/06 16:54:18 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*extract_line(char *stash)
{
	char	*line;
	char	*p;
	size_t	len;

	if (!stash || !*stash)
		return (NULL);
	p = stash;
	while (*p && *p != '\n')
		p++;
	len = p - stash + (*p == '\n');
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, stash, len);
	*(line + len) = '\0';
	return (line);
}

static char	*clean_stash(char *stash)
{
	char	*new;
	char	*p;

	p = stash;
	while (*p && *p != '\n')
		p++;
	if (!*p || !*(p + 1))
		return (free(stash), NULL);
	new = ft_strjoin(NULL, p + 1);
	return (free(stash), new);
}

static char	*read_loop(int fd, char *stash, char *buf, char *acc)
{
	int		bytes;
	size_t	i;

	bytes = 1;
	i = 0;
	while (bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		ft_memcpy(acc + i, buf, bytes);
		i += bytes;
		*(acc + i) = '\0';
		*(buf + bytes) = '\0';
		if (i + BUFFER_SIZE >= 8192 || ft_strchr(buf, '\n'))
		{
			stash = ft_strjoin(stash, acc);
			i = 0;
			*acc = '\0';
			if (ft_strchr(buf, '\n'))
				break ;
		}
	}
	if (i > 0 && bytes != -1)
		stash = ft_strjoin(stash, acc);
	return (free(buf), free(acc), (bytes == -1) ? (free(stash), NULL) : stash);
}

static char	*fill_stash(int fd, char *stash)
{
	char	*buf;
	char	*acc;
	size_t	asz;

	if (stash && ft_strchr(stash, '\n'))
		return (stash);
	asz = 8192;
	if ((size_t)BUFFER_SIZE > asz)
		asz = (size_t)BUFFER_SIZE;
	buf = malloc((size_t)BUFFER_SIZE + 1);
	acc = malloc(asz + 1);
	if (!buf || !acc)
		return (free(buf), free(acc), free(stash), NULL);
	*acc = '\0';
	return (read_loop(fd, stash, buf, acc));
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	stash[fd] = fill_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = clean_stash(stash[fd]);
	return (line);
}
