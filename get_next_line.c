/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:42:36 by miyuu             #+#    #+#             */
/*   Updated: 2024/09/08 19:31:02 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

static char	*nullize_free(char *p)
{
	free(p);
	p = NULL;
	return (NULL);
}

static bool	input_line(char *lines, char *buf, size_t read_byte)
{
	char	*memo;

	if (lines == NULL)
		lines = ft_substr(buf, 0, read_byte);
	else
	{
		memo = lines;
		lines = ft_strjoin(lines, buf);
		free(memo);
	}
	// printf("lines：%s\n", lines);
	// return (lines);
	return (lines != NULL);
}

static char	*extract_line(char *lines)
{
	char	*line_n;
	char	*line_end;
	char	*origin;
	char	*one_line;

	line_n = ft_strchr(lines, '\n');
	line_end = lines + ft_strlen(lines);
	origin = lines;
	lines = NULL;
	if (line_n == NULL || line_n + 1 == line_end)
		one_line = ft_substr(origin, 0, line_end - origin);
	else
	{
		one_line = ft_substr(origin, 0, line_n - origin + 1);
		lines = ft_substr(origin, line_n - origin + 1, line_end - line_n);
		if (one_line == NULL || lines == NULL)
		{
			nullize_free(one_line);
			nullize_free(lines);
		}
	}
	free(origin);
	return (one_line);
}

char	*get_next_line(int fd)
{
	static char	*lines;
	char		buf[BUFFER_SIZE + 1];
	size_t		read_byte;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	while (lines == NULL || ft_strchr(lines, '\n') == NULL)
	{
		read_byte = read(fd, &buf, BUFFER_SIZE);
		if (read_byte <= 0)
			return (nullize_free(lines));
		if (read_byte == 0 && lines == NULL)
			return (nullize_free(lines));
		buf[read_byte] = '\0';
		// printf("lines：%s\n", input_line(lines, buf, read_byte));
		// lines = input_line(lines, buf, read_byte);
		if (!input_line(lines, buf, read_byte))
			return (nullize_free(lines));
		if (read_byte < BUFFER_SIZE)
			break ;
	}
	return (extract_line(lines));
}


int	main(void)
{
	int		fd;
	char	*one_line;

	fd = open("./text.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	while ((one_line = get_next_line(fd)) != NULL)
	{
		printf("出力：%s", one_line);
		fflush(stdout);
		free(one_line);
	}
	printf("close");
	close(fd);
	return (0);
}
