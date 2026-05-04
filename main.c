/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:30:20 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/04 17:35:48 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int		fd1;
	int		fd2;
	char	*line;

	// 1. Abrimos dos archivos diferentes
	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);

	if (fd1 == -1 || fd2 == -1)
	{
		printf("Error al abrir los archivos de prueba.\n");
		return (1);
	}

	printf("--- Iniciando lectura alternada ---\n\n");

	// Leemos del primer archivo
	line = get_next_line(fd1);
	printf("FD %d (A): %s", fd1, line);
	free(line);

	// Leemos del segundo archivo (aquí se prueba el array estático)
	line = get_next_line(fd2);
	printf("FD %d (B): %s", fd2, line);
	free(line);

	// Volvemos al primero
	line = get_next_line(fd1);
	printf("FD %d (A): %s", fd1, line);
	free(line);

	// Volvemos al segundo
	line = get_next_line(fd2);
	printf("FD %d (B): %s", fd2, line);
	free(line);

	close(fd1);
	close(fd2);
	return (0);
}
