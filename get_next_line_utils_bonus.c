/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:13:42 by gscarama          #+#    #+#             */
/*   Updated: 2022/02/09 08:29:45 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	size;

	size = 0;
	if (!str)
		return (0);
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
	nstr[lens1] = '\0';
	return (nstr);
}

char	*ft_strndup(char *src, size_t size)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (!src[0])
	{
		free(src);
		return (NULL);
	}
	dest = malloc(sizeof(char) * size + 1);
	if (dest == NULL)
		return (NULL);
	while (src[i] && i < size && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	if (src[i])
	{
		dest[i] = '\n';
		++i;
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
	if (!s)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == uc)
			return (1);
		i++;
	}
	return (0);
}
