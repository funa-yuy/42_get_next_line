/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:42:36 by miyuu             #+#    #+#             */
/*   Updated: 2024/08/25 17:56:24 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFFER_SIZE 100

// char	*get_next_line(int fd)
// {
// 	char static	read_s;


// 	read_s = fd
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	int		i;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = strlen(s1);
	len_s2 = strlen(s2);
	i = 0;
	dst = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!dst)
		return (NULL);
	while (i < len_s1)
	{
		dst[i] = s1[i];
		i++;
	}
	while (i < len_s1 + len_s2)
	{
		dst[i] = s2[i - len_s1];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;
	size_t	s_len;

	dst = NULL;
	i = 0;
	if (!s)
		return (NULL);
	s_len = strlen(s);
	if (s_len <= start)
		len = 0;
	else if (s_len - start <= len)
		len = s_len - start;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	while (len > i)
	{
		dst[i] = s[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}


static char	*nullize_free(char **p)
{
	free(*p);
	*p = NULL;
	return (NULL);
}

static bool	pack(char **p_store, char *s, size_t	read_bytes)
{
	char	*bk;

	if (*p_store == NULL)
		*p_store = ft_substr(s, 0, read_bytes);
	else
	{
		bk = *p_store;
		*p_store = ft_strjoin(*p_store, s);
		free(bk);
	}
	return (*p_store != NULL);//NULLじゃないならtrue
}

static bool	read_and_pack(char **p_store, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	size_t	read_bytes;

	while (*p_store == NULL || strchr(*p_store, '\n') == NULL)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes < 0)
			return (false);
		if (read_bytes == 0 && *p_store == NULL)
			return (false);
		buf[read_bytes] = '\0'; //最後に終端ヌルを入れてる
		if (!pack(p_store, buf, read_bytes))
			return (false);
		if (read_bytes < BUFFER_SIZE)//１行の長さがバッファサイズより大きかったらwhileを回す
			break ;
	}
	return (true);
}

static char	*extract_line(char **p_store)
{
	char	*p_nl;
	char	*p_end;
	char	*origin;
	char	*line;

	p_nl = strchr(*p_store, '\n');//最初の改行以降の文字列
	p_end = *p_store + strlen(*p_store);//p_storeの先頭ポインターに、p_storeの文字数を足す→p_storeの末尾を指すポインタを意味する
	origin = *p_store;//元の文字列
	*p_store = NULL;
	if (p_nl == NULL || p_nl + 1 == p_end)//改行がないか、改行が最後の文字だったら
		line = ft_substr(origin, 0, p_end - origin);
	else
	{
		line = ft_substr(origin, 0, p_nl - origin + 1);//元の文字列の0文字目から、
		*p_store = ft_substr(origin, p_nl - origin + 1, p_end - p_nl);
		if (line == NULL || *p_store == NULL)
		{
			nullize_free(&line);
			nullize_free(p_store);
		}
	}
	free(origin);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*read_s;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > SIZE_MAX - 1)
		return (NULL);
	if (!read_and_pack(&read_s, fd))
		return (nullize_free(&read_s));
	return (extract_line(&read_s));
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
