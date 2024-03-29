/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:13:42 by gscarama          #+#    #+#             */
/*   Updated: 2022/02/14 08:29:45 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *str)
{
	free(str);
	return (0);
}

char	*ft_fdline(char *rest, int fd)
{
	char	*buf;
	ssize_t	r_bytes;

	buf = malloc(sizeof(buf) * BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	r_bytes = 1;
	while (!ft_strchr(rest, '\n') && r_bytes > 0)
	{
		r_bytes = read(fd, buf, BUFFER_SIZE);
		if (r_bytes < 0)
			return (ft_free(buf));
		if (!rest)
		{
			rest = malloc(sizeof(char) * 1);
			if (!rest)
				return (ft_free(buf));
			rest[0] = '\0';
		}
		rest = ft_strnjoin(rest, buf, r_bytes);
		if (!rest)
			return (ft_free(buf));
	}
	free(buf);
	return (rest);
}

char	*ft_fdover(char *rest, ssize_t size)
{
	char	*tmp;
	ssize_t	end;

	end = 0;
	if (!rest[size])
		return (ft_free(rest));
	end = ft_strlen(&rest[size + 1]);
	tmp = malloc(sizeof(char) * (end + 1));
	if (!tmp)
		return (ft_free(rest));
	end = 0;
	while (rest[size + end + 1])
	{
		tmp[end] = rest[size + end + 1];
		end++;
	}
	tmp[end] = '\0';
	free(rest);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*dst;
	ssize_t		size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	size = 0;
	rest = ft_fdline(rest, fd);
	if (!rest)
		return (0);
	while (rest[size] && rest[size] != '\n')
		size++;
	dst = ft_strndup(rest, size + 1);
	rest = ft_fdover(rest, size);
	return (dst);
}

// #include <stdio.h>
// #include <fcntl.h>
// int	main(void)
// {
// 	char	*ret;
// 	int		fd;
// 	int		i;

// 	fd = open("test1.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		printf("OPEN ERROR\n");
// 		return (0);
// 	}
// 	i = 0;
// 	while (i < 4)
// 	{
// 		ret = get_next_line(fd);
// 		printf("Str[%i]: %s", i, ret);
// 		free(ret);
// 		++i;
// 	}
// 	return (0);
// }
