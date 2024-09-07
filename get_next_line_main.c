/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:42:36 by miyuu             #+#    #+#             */
/*   Updated: 2024/09/07 19:29:23 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*nullize_free(char *p)
{
	free(p);
	p = NULL;
	return (NULL);
}


static void	input_line(char *lines, char *buf, size_t read_byte)
{
	char	*memo;

	if (lines == NULL)
		lines = ft_substr(buf, 0, read_byte);//linesに入れる
	else
	{
		memo = lines;
		lines = ft_strjoin(lines, buf); //ft_strjoinで、linesと bufを連結
		free(memo);
	}
	if (lines == NULL)
		nullize_free(lines);

}

static char	*extract_line(char *lines)
{
	char	*line_n;
	char	*line_end;
	char	*origin;
	char	*one_line;

	line_n = ft_strchr(lines, '\n');//最初の改行以降の文字列
	line_end = lines + ft_strlen(lines);//linesの先頭ポインターに、linesの文字数を足す→linesの末尾を指すポインタを意味する
	origin = lines;//元の文字列も先頭ポインター
	lines = NULL;
	if (line_n == NULL || line_n + 1 == line_end)//改行がないか、改行が最後の文字だったら
		one_line = ft_substr(origin, 0, line_end - origin);
	else
	{
		one_line = ft_substr(origin, 0, line_n - origin + 1);//元の文字列の0文字目から、改行まで
		lines = ft_substr(origin, line_n - origin + 1, line_end - line_n);//改行以降の文字列
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
		read_byte = read(fd, &buf, BUFFER_SIZE); //BUFFER_SIZE分リード
		if (read_byte <= 0)
			nullize_free(lines);
		if (read_byte == 0 && lines == NULL)
			nullize_free(lines);
		buf[read_byte] = '\0';//最後に終端ヌル
		input_line(lines, buf, read_byte);
		// if (lines == NULL)
		// 	lines = ft_substr(buf, 0, read_byte);//linesに入れる
		// else
		// {
		// 	memo = lines;
		// 	lines = ft_strjoin(lines, buf); //ft_strjoinで、linesと bufを連結
		// 	free(memo);
		// }
		// if (lines == NULL)
		// 	nullize_free(&lines);
		if (read_byte < BUFFER_SIZE)//１行の長さがバッファサイズより大きかったらwhileを回す
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
		free(one_line); //malloc使ってないからfreeはコメントアウト
	}
	printf("close");
	close(fd);
	return (0);
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
	// newline_pos = ft_strchr(buf, '\n');
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

// int main() {
//     int fd;
//     char *line;

//     // ファイルを開く
//     fd = open("./text.txt", O_RDONLY);
//     if (fd == -1) {
//         perror("open");
//         return (1);
//     }
//     // while ((line = get_next_line(fd)) != NULL) {
//     //     printf("%s", line);
// 	// 	fflush(stdout);
//     //     free(line);
//     // }
//     close(fd);
//     return (0);
// }
