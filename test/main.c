/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:30:20 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/04 23:45:42 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd1;
    int     fd2;
    char    *line1;
    char    *line2;
    int     active_1;
    int     active_2;

    fd1 = open("test_big.txt", O_RDONLY);
    fd2 = open("text2.txt", O_RDONLY);
    if (fd1 < 0 || fd2 < 0)
        return (printf("Error al abrir archivos\n"), 1);

    active_1 = 1;
    active_2 = 1;
    while (active_1 || active_2)
    {
        // Intentar leer del primero
        if (active_1 && (line1 = get_next_line(fd1)))
        {
            printf("FD %d: %s", fd1, line1);
            free(line1);
        }
        else
            active_1 = 0; // Se acabó el archivo 1

        // Intentar leer del segundo
        if (active_2 && (line2 = get_next_line(fd2)))
        {
            printf("FD %d: %s", fd2, line2);
            free(line2);
        }
        else
            active_2 = 0; // Se acabó el archivo 2
    }

    close(fd1);
    close(fd2);
    return (0);
}
