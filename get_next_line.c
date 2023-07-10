/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-innoc <gd-innoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:46:31 by gd-innoc          #+#    #+#             */
/*   Updated: 2023/07/10 15:28:44 by gd-innoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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