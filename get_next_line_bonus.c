/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:13:42 by gscarama          #+#    #+#             */
/*   Updated: 2022/02/09 08:29:45 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*ft_fdline(char *rest, int fd)
{
	char	buf[BUFFER_SIZE];
	ssize_t	r_bytes;

	r_bytes = 1;
	while (!ft_strchr(rest, '\n') && r_bytes > 0)
	{
		r_bytes = read(fd, buf, BUFFER_SIZE);
		if (r_bytes < 0)
			return (0);
		if (!rest && r_bytes > 0)
		{
			rest = malloc(sizeof(char) * 1);
			if (!rest)
				return (0);
			rest[0] = '\0';
		}
		rest = ft_strnjoin(rest, buf, r_bytes);
		if (!rest)
			return (0);
	}
	return (rest);
}

char	*ft_fdover(char *rest, ssize_t size)
{
	char	*tmp;
	ssize_t	end;

	end = 0;
	if (!rest[size])
	{
		free(rest);
		return (0);
	}
	end = ft_strlen(&rest[size + 1]);
	tmp = malloc(sizeof(char) * (end + 1));
	if (!tmp)
		return (0);
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
	static char	*rest[10240];
	char		*dst;
	ssize_t		size;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 10240)
		return (0);
	size = 0;
	rest[fd] = ft_fdline(rest[fd], fd);
	if (!rest[fd])
		return (0);
	while (rest[fd][size] && rest[fd][size] != '\n')
		size++;
	dst = ft_strndup(rest[fd], size + 1);
	if (!dst)
		return (0);
	rest[fd] = ft_fdover(rest[fd], size);
	return (dst);
}
