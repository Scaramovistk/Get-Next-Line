/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:13:42 by gscarama          #+#    #+#             */
/*   Updated: 2022/02/09 08:29:45 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strnjoin(char const *s1, char const *s2, int i);
char	*ft_strndup(char *src, size_t size);
int		ft_strchr(const char *s, int c);
char	*get_next_line(int fd);
char	*ft_fdover(char *rest, ssize_t size);
char	*ft_fdline(char *rest, int fd);

#endif