/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:38:25 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/05 17:13:32 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*fill_stash(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read;

	// Si ya tenemos un \n en el stash sobrante de la llamada anterior, salimos
	if (stash && ft_strchr(stash, '\n'))
		return (stash);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(stash), NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(stash), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash || ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (stash);
}

// 1. fill_stash: BUSCA SOLO EN EL BUFFER (Ya lo tienes, mantenlo así)
// 2. extract_line: Mide y extrae en un solo paso
char	*extract_line(char *stash)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!stash || !stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	// i + (si hay \n) + 1 para \0
	line = malloc(i + (stash[i] == '\n') + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, stash, i + (stash[i] == '\n'));
	line[i + (stash[i] == '\n')] = '\0';
	return (line);
}

// 3. clean_stash: Usa la posición que ya conocemos
char	*clean_stash(char *stash)
{
	char	*new_stash;
	size_t	i;
	size_t	len;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	// Si no hay \n o no hay nada después, liberamos y fuera
	if (!stash[i] || !stash[i + 1])
	{
		free(stash);
		return (NULL);
	}
	// Medimos lo que queda DESDE la posición i
	len = ft_strlen(stash + i + 1);
	new_stash = malloc(len + 1);
	if (!new_stash)
		return (free(stash), NULL);
	ft_memcpy(new_stash, stash + i + 1, len + 1);
	free(stash);
	return (new_stash);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	// Si el inicio está fuera del string, devolvemos string vacío
	if (start >= s_len)
	{
		substr = malloc(1);
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	// Si lo que pedimos copiar es más de lo que hay, ajustamos len
	if (len > s_len - start)
		len = s_len - start;
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	// Usamos memcpy para que la copia sea ultra rápida
	ft_memcpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
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
	// Si extract_line no pudo sacar nada (ej. error de malloc), 
	// liberamos el stash para evitar leaks.
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = clean_stash(stash[fd]);
	return (line);
}

