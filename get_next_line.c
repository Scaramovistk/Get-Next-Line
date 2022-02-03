/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 20:13:42 by gscarama          #+#    #+#             */
/*   Updated: 2022/01/18 08:29:45 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_fdline(char *rest, int fd)
{
	char	buf[BUFFER_SIZE];
	ssize_t	r_bytes;

	r_bytes = 1;
	while (!ft_strchr(rest, '\n') && r_bytes > 0)
	{
		r_bytes = read(fd, buf, BUFFER_SIZE);
		if (r_bytes <= 0)
			return (0);
		if (!rest)
		{
			rest = malloc(sizeof(char) * 1);
			if (!rest)
				return (0);
			rest[0] = '\0';
		}
		rest = ft_strnjoin(rest, buf, r_bytes);
	}
	return (rest);
}

char	*ft_fdover(char *rest, int size)
{
	int		end;
	char	*tmp;

	end = 0;
	while (rest[end + size])
		end++;
	tmp = ft_strndup(rest + size, end);
	if (!tmp)
		return (0);
	free(rest);
	rest = ft_strndup(tmp, end);
	if (!rest)
		return (0);
	free(tmp);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*dst;
	int			size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	size = 0;
	rest = ft_fdline(rest, fd);
	if (0 == rest)
		return (0);
	while (rest[size] && rest[size] != '\n')
		size++;
	if (size == 0)
	{
		if (1)
			free(rest);
		return (0);
	}
	dst = ft_strndup(rest, size + 1);
	if (!dst)
		return (0);
	rest = ft_fdover(rest, size);
	return (dst);
}

// #include <stdio.h>
// #include <fcntl.h>
// int	main(void)
// {
// 	char	*ret;
// 	int		fd;
// 	size_t	i;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		printf("OPEN ERROR\n");
// 		return (0);
// 	}
// 	i = 0;
// 	while (i < 2)
// 	{
// 		ret = get_next_line(fd);
// 		printf("Str: %s\n", ret);
// 		free(ret);
// 		++i;
// 	}
// 	return (0);
// }
