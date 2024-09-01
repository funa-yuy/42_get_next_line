/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:42:36 by miyuu             #+#    #+#             */
/*   Updated: 2024/08/28 22:31:08 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFFER_SIZE 100


char	*ft_strdup(const char *s1);




char	gnl_read_line(int fd, char *lines)
{
	char	buf[BUFFER_SIZE];
	size_t	read_byte;
	char	*newline;

	while (ft_strchr(buf, '\n') != NULL)
	read_byte = read(fd, &buf, BUFFER_SIZE);
	if (read_byte <= 0)
		return (NULL);



	if (ft_strchr(lines, '\n') == NULL)
		newline = ft_strdup(lines);
		return (newline);
	else
		char *front;
		char *back;

		back = ft_strchr(lines, '\n');
		front = strlen(lines) - strlen(back);








}


char	*get_next_line(int fd)
{
	static char	*lines;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	gnl_read_line(fd, &lines);
	if (!read_and_pack(&lines, fd))
		return (nullize_free(&lines));
	return (extract_line(&lines));
}

// int	main()
// {

// 	int  fd;
	// char buf[100];
	// char buf_n[100];
	// char static	memo[100];
	// int byte_num;
	// char *newline_pos;


	// byte_num = 0;
	//  memset(buf, '\0', 100);
	//  memset(buf_n, '\0', 100);
	//  	memset(memo, '\0', 100);

	// fd = open("./text.txt", O_RDONLY);
	// if(fd == -1)
    // 	{
    //     	fprintf(stdout, "ファイルオープンエラー\n");
    //    		 return 1;
   	//  }
	// for (size_t i = 0; i < 3; i++)
	// {
	// 	printf ("%s", get_next_line(fd));
	// }

	// int i = 0;
	// while (buf[i] != '\n')
	// {
	// 	 byte_num = read(fd, &buf, BUFFER_SIZE);
	//    if(byte_num == -1)
	// 	{
	// 		fprintf(stdout, "ファイル読み込みエラー\n");
	// 		return 1;
	// 	}
	// 	i++;
	// }
	// printf("fileから%dバイト読み込みました。\n", byte_num);
	// // 改行文字を探す
	// newline_pos = strchr(buf, '\n');
	// if (newline_pos != NULL)
	// {
	// 	// 改行文字までの部分を buf_n にコピー
	// 	strncpy(buf_n, buf, newline_pos - buf);

	// 	// 改行文字以降を memo にコピー
	// 	strcpy(memo, newline_pos + 1);
	// }

	// 	fprintf(stdout, "読み込んだ文字列:%s\n", buf);
	// fprintf(stdout, "改行までの文字列:%s\n", buf_n);
	// fprintf(stdout, "改行以降の文字列:%s\n", memo);

// 	close(fd);

//  return (0);
// }

int main() {
    int fd;
    char *line;

    // ファイルを開く
    fd = open("./text.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return (1);
    }
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
		fflush(stdout);
        free(line);
    }
    close(fd);
    return (0);
}
