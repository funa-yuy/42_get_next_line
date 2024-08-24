/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:42:36 by miyuu             #+#    #+#             */
/*   Updated: 2024/08/17 18:30:33 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 1

// char	*get_next_line(int fd)
// {
// 	char static	memo;

// 	memo = fd
// }


int	main()
{

	int  fd;
	char buf[100];
	char buf_n[100];
	char static	memo[100];
	int byte_num;
	char *newline_pos;


	byte_num = 0;
	 memset(buf, '\0', 100);
	 memset(buf_n, '\0', 100);
	 	memset(memo, '\0', 100);

	fd = open("./text.txt", O_RDONLY);

	if(fd == -1)
    	{
        	fprintf(stdout, "ファイルオープンエラー\n");
       		 return 1;
   	 }
	int i = 0;
	while (buf[i] != '\n')
	{
		 byte_num = read(fd, &buf, BUF_SIZE);
	   if(byte_num == -1)
		{
			fprintf(stdout, "ファイル読み込みエラー\n");
			return 1;
		}
		i++;
	}
	fprintf(stdout, "fileから%dバイト読み込みました。\n", byte_num);
	// 改行文字を探す
	newline_pos = strchr(buf, '\n');
	if (newline_pos != NULL)
	{
		// 改行文字までの部分を buf_n にコピー
		strncpy(buf_n, buf, newline_pos - buf);

		// 改行文字以降を memo にコピー
		strcpy(memo, newline_pos + 1);
	}

		fprintf(stdout, "読み込んだ文字列:%s\n", buf);
	fprintf(stdout, "改行までの文字列:%s\n", buf_n);
	fprintf(stdout, "改行以降の文字列:%s\n", memo);

	close(fd);

 return (0);
}
