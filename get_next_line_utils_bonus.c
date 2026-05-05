/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:49:23 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/05 17:13:45 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	size_t	len_s;
	size_t	len_b;

	if (!stash)
	{
		stash = malloc(1);
		stash[0] = '\0';
	}
	if (!stash || !buffer)
		return (free(stash), NULL);
	len_s = ft_strlen(stash);
	len_b = ft_strlen(buffer);
	new_str = malloc(len_s + len_b + 1);
	if (!new_str)
		return (free(stash), NULL);
	// Usar memoria directa es más rápido que loops de caracteres
	ft_memcpy(new_str, stash, len_s);
	ft_memcpy(new_str + len_s, buffer, len_b + 1);
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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dst);
}
