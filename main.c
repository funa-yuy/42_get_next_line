
#include <stdio.h>
#include "get_next_line.h"


static char	*nullize_free(char **p)
{
	free(*p);
	*p = NULL;
	return (NULL);
}

static bool	input_line(char **lines, char *buf, size_t read_byte)
{
	char	*memo;

	if (*lines == NULL)
		*lines = ft_substr(buf, 0, read_byte);
	else
	{
		memo = *lines;
		*lines = ft_strjoin(*lines, buf);
		free(memo);
	}
	return (*lines != NULL);
}

static char	*extract_line(char **lines)
{
	char	*line_n;
	char	*line_end;
	char	*origin;
	char	*one_line;

	line_n = ft_strchr(*lines, '\n');  // linesの中に改行文字があるかを探す
	line_end = *lines + ft_strlen(*lines);	// lines全体の長さを計算し、その終端を指すポインタを取得
	origin = *lines;// linesの元のポインタをoriginに保存しておく（後でfreeするため）
	*lines = NULL;
	 // 改行がないか、改行が行末（最後の文字）の場合、1行全体を切り出す
	if (line_n == NULL || line_n + 1 == line_end)
		one_line = ft_substr(origin, 0, line_end - origin);
	else
	{
		one_line = ft_substr(origin, 0, line_n - origin + 1);  // 改行がある場合、その改行までを含めて部分文字列を取得
		*lines = ft_substr(origin, line_n - origin + 1, line_end - line_n);
		if (one_line == NULL || *lines == NULL)
		{
			nullize_free(&one_line);
			nullize_free(lines);
		}
	}
	free(origin);
	return (one_line);
}

static char	*read_line_error(char **lines, char *buf)
{
	free(buf);
	return (nullize_free(lines));
}

char	*get_next_line(int fd)
{
	static char	*lines;// 静的変数。関数の呼び出しをまたいで前回のデータを保持するためのバッファ
	char		*buf;// 読み込んだデータを一時的に保持するためのバッファ
	ssize_t		read_byte;// read関数で読み込んだバイト数を格納する変数

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));// BUFFER_SIZE + 1のサイズでバッファをメモリ上に確保
	if (!buf)
		return (NULL);
	while (lines == NULL || ft_strchr(lines, '\n') == NULL)
	{
		read_byte = read(fd, buf, BUFFER_SIZE);
		// printf("\nread_byte = %zd\n", read_byte);
		// printf("lines = %s\n", lines);
		if (read_byte < 0)
			return (read_line_error(&lines, buf));
		if (read_byte == 0 && lines == NULL)
			return (read_line_error(&lines, buf));
		buf[read_byte] = '\0';
		if (!input_line(&lines, buf, read_byte))// 読み込んだデータをlinesに追加。失敗した場合はエラーハンドリング
			return (read_line_error(&lines, buf));
		// printf("input_line後 = %s\n", lines);
		if (read_byte < BUFFER_SIZE)
			break ;
	}
	free(buf);//bufはローカル変数のため、この関数が終了すると、buf自体が消滅（スタックから削除)される。そのため、bufにNULLを代入する必要はない
	return (extract_line(&lines));
}

// int	main()
int	main(int argc, char *argv[])
{
	int		fd;
	char	*one_line;
	// (void)	argc;
	// (void)	argv;

	if (argc <= 1){
		printf("Give file name to process");
		return(1);
	}
	// printf("%s\n", argv[1]);
	fd = open(argv[1], O_RDONLY);
	// fd = 0;
	// fd = open("./char1.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error :fd is %d.", fd);
		perror("open");
		return (1);
	}
	while ((one_line = get_next_line(fd)) != NULL)
	{
		printf("出力結果%s", one_line);
		fflush(stdout);
		free(one_line);
	}
	// printf("close");
	close(fd);
	return (0);
}
