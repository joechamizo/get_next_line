/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 21:38:22 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/10 22:59:44 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	dealloc_list(t_list **list, t_list *clean_node)
{
	t_list	*tmp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->str_buf);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node && clean_node->str_buf[0])
		*list = clean_node;
	else if (clean_node)
	{
		free(clean_node->str_buf);
		free(clean_node);
	}
}

void	refine_list(t_list **list)
{
	t_list	*last;
	t_list	*clean;
	int		i;
	int		j;

	i = 0;
	j = 0;
	clean = malloc(sizeof(t_list));
	last = find_last_node(*list);
	if (!clean || !last)
		return (free(clean));
	clean->next = NULL;
	while (last->str_buf[i] && last->str_buf[i] != CUT_CHAR)
		i++;
	if (last->str_buf[i] == CUT_CHAR)
		i++;
	while (last->str_buf[i + j])
		j++;
	clean->str_buf = malloc(j + 1);
	j = 0;
	while (last->str_buf[i])
		clean->str_buf[j++] = last->str_buf[i++];
	clean->str_buf[j] = '\0';
	dealloc_list(list, clean);
}

char	*get_line_from_list(t_list *list)
{
	int		len;
	char	*str;

	if (!list)
		return (NULL);
	len = len_until_newline(list);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	copy_str(list, str);
	return (str);
}

void	create_list(t_list **list, int fd)
{
	int		n;
	char	*buf;

	while (!found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		n = read(fd, buf, BUFFER_SIZE);
		if (n <= 0)
		{
			free(buf);
			if (n == -1)
				dealloc_list(list, NULL);
			return ;
		}
		buf[n] = '\0';
		append_node(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list[1024];
	char			*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&list[fd], fd);
	if (!list[fd])
		return (NULL);
	line = get_line_from_list(list[fd]);
	refine_list(&list[fd]);
	return (line);
}
