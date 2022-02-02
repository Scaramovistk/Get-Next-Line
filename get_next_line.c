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

//#include "get_next_line.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


size_t	ft_strlen(const char *str)
{
	size_t		size;

	size = 0;
	while (str[size] != '\0')
		size++;
	return (size);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	lendst;
	size_t	lensrc;
	size_t	rest;

	i = 0;
	rest = size;
	while (dst[i] && rest > 0)
	{
		rest--;
		i++;
	}
	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	if (rest == 0)
		return (lensrc + size);
	i = 0;
	while (rest > 1 && src[i] != '\0')
	{
		dst[(lendst + i)] = src[i];
		rest--;
		i++;
	}
	dst[(lendst + i)] = '\0';
	return (lendst + lensrc);
}

char	*ft_strnjoin(char const *s1, char const *s2, int i)
{
	size_t	len;
	size_t	lens1;
	int		j;
	char	*nstr;

	j = 0;
	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	len = lens1 + i + 1;
	nstr = malloc(sizeof(char) * len);
	if (!nstr)
		return (NULL);
	nstr[0] = '\0';
	ft_strlcat(nstr, s1, len);
	while (j != i)
	{
		nstr[lens1] = s2[j];
		lens1++;
		j++;
	}
	free((void *)s1);
	return (nstr);
}

static char	*ft_strndup(char const *src, size_t size)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * size + 1);
	if (dest == NULL)
		return (NULL);
	while (src[i] && i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	*str;
	unsigned char	uc;

	str = (unsigned char *)s;
	uc = (unsigned char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == uc)
			return (1);
		i++;
	}
	return (0);
}

//////////////////////////////

char	*ft_fdline(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	char	*dst;
	char	*rest;
	int		size;
	int		i;
	int		j;

	size = 0;
	i = 0;
	rest = (char *)'\0';
	while (1)
	{
		read(fd, buf, BUFFER_SIZE);
		rest = ft_strnjoin(rest, buf, BUFFER_SIZE);
		j = 0;
		while (j != BUFFER_SIZE)
		{
			if (buf[j + i] == '\0')
			{
				while (buf[size])
					size++;
				dst = ft_strndup(buf, size);
				return (dst);
			}
			j++;
		}
		i++;
	}
	// while (!ft_strchr(buf, '\0') && BUFFER_SIZE != 0)
	// {
	// 	read(fd, buf, BUFFER_SIZE);
	// 	rest = ft_strnjoin(rest, buf, BUFFER_SIZE);
	// }
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*dst;
	int			size;
	static int	bg;
	int			end;

	end = 0;
	size = 0;
	if (!bg)
		bg = 0;
	buf = ft_fdline(fd);
	while (buf[size + bg] != '\n' && buf[size + bg])
		size++;
	dst = ft_strndup(buf + bg, size); //Need protection for malloc
	bg += size;
	return (dst);
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*ret;
	int		fd;
	size_t	i;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("OPEN ERROR\n");
		return (0);
	}
	i = 0;
	while (i < 2)
	{
		ret = get_next_line(fd);
		printf("Str: %s\n", ret);
		free(ret);
		++i;
	}
	return (0);
}

