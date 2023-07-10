/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-innoc <gd-innoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:46:31 by gd-innoc          #+#    #+#             */
/*   Updated: 2022/12/19 15:08:53 by gd-innoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*GET_NEXT_LINE
---------------
This function reads from an open file descriptor and returns the text read 
until (and including) the first newline char it encounters. On next calls it 
returns the next line, or null if the file has ended or an error has occurred.
---------------
AUXILIARY FUNCTIONS:
---------------
- read_to_str
Takes as parameter the static var left_str (empty on first call) and the fd we
are reading from. Allocates memory with malloc to create the temporary variable
buf, in which is saved what read from the fd on each call; buf is then added 
at the end of left_str, and this is repeated until a newline char is found in
left_str. Memory for buf is freed. 
Returns the static var left_str, including the newline char, which will then 
be split into line (from 0 till the \n) and left_str (what remains after
the current \n and before the previous one).
---------------
-ft_get_line.
Takes as parameter the static var left_str, and returns the line until (and
including) the first \n it encounters.
Memory for the line is allocated with malloc. Left_line is not manipulated as
needed in the next function, to extract and maintain the chars left after \n
---------------
-ft_update_left_str
Takes as parameter the left_str (returned from read_to_str) and returns the 
string left after the \n, to keep it memory for the next call.
*/

char	*read_to_str(int fd, char *left_str)
{
	char	*buf;
	int		bytes_read;

	bytes_read = 1;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while (!ft_strchr(left_str, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{	
			free(buf);
			free(left_str);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		left_str = ft_strjoin(left_str, buf);
	}	
	free(buf);
	return (left_str);
}

char	*get_next_line(int fd)
{
	static char	*left_str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left_str = read_to_str(fd, left_str);
	if (!left_str)
		return (NULL);
	line = ft_get_line(left_str);
	left_str = update_left_str(left_str);
	return (line);
}

/*
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	fd1 = open("./dante.txt", O_RDONLY);
	i = 1;
	while (i < 20)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}*/