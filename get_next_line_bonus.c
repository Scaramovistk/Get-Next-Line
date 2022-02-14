/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:13:42 by gscarama          #+#    #+#             */
/*   Updated: 2022/02/14 08:29:45 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char *str)
{
	free(str);
	return (0);
}

char	*ft_fdline(char *rest, int fd)
{
	char	*buf;
	ssize_t	r_bytes;

	r_bytes = 1;
	buf = malloc(sizeof(buf) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	while (!ft_strchr(rest, '\n') && r_bytes > 0)
	{
		r_bytes = read(fd, buf, BUFFER_SIZE);
		if (r_bytes < 0)
			return (ft_free(buf));
		if (!rest && r_bytes > 0)
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
	static char	*rest[1024];
	char		*dst;
	ssize_t		size;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (0);
	size = 0;
	rest[fd] = ft_fdline(rest[fd], fd);
	if (!rest[fd])
		return (0);
	while (rest[fd][size] && rest[fd][size] != '\n')
		size++;
	dst = ft_strndup(rest[fd], size + 1);
	rest[fd] = ft_fdover(rest[fd], size);
	return (dst);
}
