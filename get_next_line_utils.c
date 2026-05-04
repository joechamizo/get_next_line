/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:49:23 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/05 00:34:27 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	const char	*p;

	if (!s)
		return (0);
	p = s;
	while (*p)
		p++;
	return (p - s);
}

char	*ft_strjoin(char *stash, char *buffer)
{
	char	*new_str;
	char	*s;
	char	*d;

	if (!stash)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	if (!buffer)
		return (free(stash), NULL);
	new_str = malloc(ft_strlen(stash) + ft_strlen(buffer) + 1);
	if (!new_str)
		return (free(stash), NULL);
	s = stash;
	d = new_str;
	while (*s)
		*d++ = *s++;
	while (*buffer)
		*d++ = *buffer++;
	*d = '\0';
	free(stash);
	return (new_str);
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*dest;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	dest = str;
	s += start;
	while (len--)
		*dest++ = *s++;
	*dest = '\0';
	return (str);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	char	*d;

	dest = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dest)
		return (NULL);
	d = dest;
	while (*s1)
		*d++ = *s1++;
	*d = '\0';
	return (dest);
}
