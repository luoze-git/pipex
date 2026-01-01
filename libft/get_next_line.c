/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:09:11 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/01 16:15:00 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief free pending_content and line,ie.
/// deal with malloc and set to NULL to avoid double free
/// @param pending_content
/// @return NULL
void	*reset_return_null(char **pending_content)
{
	free(*pending_content);
	*pending_content = NULL;
	return (NULL);
}

/// @brief syscalls of read() in a loop.
/// stop when new line is met or bytes_read is 0.
/// update the static array before return.
/// @param pending
/// @param hd_stat
/// @param fd
/// @return the next line
char	*reading_loop_body_of_get_next_line(char **pending, char *hd_stat,
		int fd)
{
	int		bytes_read;
	char	temp[BUFFER_SIZE + 1];
	char	*ret;

	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
			return (reset_return_null(pending));
		temp[bytes_read] = '\0';
		if (bytes_read == 0)
			return (*pending);
		if (gnl_has_newline(temp))
		{
			ret = gnl_join(*pending, temp, '\n');
			free(*pending);
			ft_update_static_array(hd_stat, temp);
			return (ret);
		}
		ret = gnl_join(*pending, temp, '\0');
		free(*pending);
		*pending = ret;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	hd_stat[BUFFER_SIZE + 1];
	char		*pending;
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	pending = NULL;
	if (hd_stat[0] && gnl_has_newline(hd_stat))
	{
		ret = gnl_join(NULL, hd_stat, '\n');
		ft_update_static_array(hd_stat, hd_stat);
		return (ret);
	}
	if (hd_stat[0])
	{
		pending = gnl_join(NULL, hd_stat, '\0');
		ft_update_static_array(hd_stat, NULL);
	}
	return (reading_loop_body_of_get_next_line(&pending, hd_stat, fd));
}

// // ------------------main for bonus
// #include "get_next_line_bonus.h"
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int main(int argc, char **argv)
// {
//     //reveive two files as input from user
//     if (argc < 3)
//     {
//         printf("Usage: %s <filename1> <filename2>\n", argv[ 0]);
//         return (1);

//     }

//     int   fd1 = open(argv[1], O_RDONLY);
//     int  fd2 = open(argv[2], O_RDONLY);

//     // return the first line of fd1
//     char *line1 = get_next_line(fd1);
//     if (line1)
//     {
//         printf("FIRST LINE FD1: %s", line1);
//         free(line1);
//     }
//     // return fd2 until EOF
//     char *line2;
//     printf("\n=== FULL LOOP FD2 UNTIL EOF ===\n");
//     while ((line2 = get_next_line(fd2)))
//     {
//         printf("LOOP FD2: %s", line2);
//         free(line2);
//     }
//     // return the next line of fd1
//     line1 = get_next_line(fd1);
//     if (line1)
//     {
//         printf("\nNEXT LINE FD1: %s", line1);
//         free(line1);
//     }
//     close(fd1);
//     close(fd2);
//     return (0);
// }

// // ------------------main for mandatory
// #include "get_next_line.h"
// #include <fcntl.h>
// #include <stdio.h>

// int main(int argc, char **argv)
// {
//     int   fd;
//     char *line;

//     if (argc < 2)
//     {
//         printf("Usage: %s <filename>\n", argv[0]);
//         return (1);
//     }

//     // ---- Part 1: read until EOF ----
//     fd = open(argv[1], O_RDONLY);
//     if (fd < 0)
//     {
//         perror("open");
//         return (1);
//     }
//     printf("=== FULL LOOP UNTIL EOF ===\n");
//     while ((line = get_next_line(fd)))
//     {
//         printf("LOOP: %s", line);
//         free(line);
//     }
//     close(fd);

//     // ---- Part 2: only first line ----
//     fd = open(argv[1], O_RDONLY);
//     if (fd < 0)
//     {
//         perror("open");
//         return (1);
//     }
//     printf("\n=== ONLY FIRST LINE ===\n");
//     line = get_next_line(fd);
//     if (line)
//     {
//         printf("FIRST LINE: %s", line);
//         free(line);
//     }
//     close(fd);

//     // read from stdin fd -- 0 ----
//     fd = 0;
//     printf("=== FULL LOOP UNTIL EOF ===\n");
//     while ((line = get_next_line(fd)))
//     {
//         printf("LOOP: %s", line);
//         free(line);
//     }

//     // ---- Part 2: only first line ----
//     if (fd < 0)
//     {
//         perror("open");
//         return (1);
//     }
//     printf("\n=== ONLY FIRST LINE ===\n");
//     line = get_next_line(fd);
//     if (line)
//     {
//         printf("FIRST LINE: %s", line);
//         free(line);
//     }
//     return (0);
// }
