/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:38:25 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/07 18:16:28 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *s)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!s || !*s)
		return (NULL);
	while (s[i] && s[i] != CUT_CHAR)
		i++;
	if (s[i] == CUT_CHAR)
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != CUT_CHAR)
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == CUT_CHAR)
		line[i++] = CUT_CHAR;
	line[i] = '\0';
	return (line);
}

static char	*clean_stash(char *s)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i] && s[i] != CUT_CHAR)
		i++;
	if (!s[i] || !s[i + 1])
	{
		free(s);
		return (NULL);
	}
	new = malloc(ft_strlen(s) - i);
	if (!new)
	{
		free(s);
		return (NULL);
	}
	i++;
	j = 0;
	while (s[i])
		new[j++] = s[i++];
	new[j] = '\0';
	free(s);
	return (new);
}

static int	read_loop(int fd, char **stash, char *buf, char *acc)
{
	int		b;
	size_t	i;

	b = 1;
	i = 0;
	while (b > 0)
	{
		b = read(fd, buf, BUFFER_SIZE);
		if (b <= 0)
			break ;
		buf[b] = '\0';
		ft_memcpy(acc + i, buf, (size_t)b);
		i += b;
		acc[i] = '\0';
		if (ft_strchr(buf, CUT_CHAR) || i + (size_t)BUFFER_SIZE >= 8000)
		{
			*stash = ft_manage_acc(*stash, acc, &i);
			if (ft_strchr(buf, CUT_CHAR))
				break ;
		}
	}
	if (i > 0 && b != -1)
		*stash = ft_strjoin(*stash, acc);
	return (b);
}

static char	*init_and_read(int fd, char *stash)
{
	char	*buf;
	char	*acc;
	int		b;

	buf = malloc((size_t)BUFFER_SIZE + 1);
	acc = malloc(8192 + (size_t)BUFFER_SIZE + 1);
	if (!buf || !acc)
	{
		free(buf);
		free(acc);
		return (NULL);
	}
	acc[0] = '\0';
	b = read_loop(fd, &stash, buf, acc);
	free(buf);
	free(acc);
	if (b == -1)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*st[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	if (!st[fd] || !ft_strchr(st[fd], CUT_CHAR))
		st[fd] = init_and_read(fd, st[fd]);
	if (!st[fd])
		return (NULL);
	line = extract_line(st[fd]);
	if (!line)
	{
		free(st[fd]);
		st[fd] = NULL;
		return (NULL);
	}
	st[fd] = clean_stash(st[fd]);
	return (line);
}
