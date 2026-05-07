/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:49:23 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/07 10:28:14 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	l1;
	size_t	l2;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	res = malloc(l1 + l2 + 1);
	if (!res)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	ft_memcpy(res, s1, l1);
	ft_memcpy(res + l1, s2, l2);
	res[l1 + l2] = '\0';
	if (s1)
		free(s1);
	return (res);
}

char	*ft_manage_acc(char *stash, char *acc, size_t *i)
{
	char	*new_stash;

	new_stash = ft_strjoin(stash, acc);
	*i = 0;
	acc[0] = '\0';
	return (new_stash);
}
