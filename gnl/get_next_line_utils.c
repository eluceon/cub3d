/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 07:10:12 by eluceon           #+#    #+#             */
/*   Updated: 2020/12/28 11:04:14 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	len = 0;
	while (s1[len])
		len++;
	while (s2[i])
		i++;
	len += i;
	if (!(new_str = (char *)malloc(sizeof(new_str) * (len + 1))))
		return (NULL);
	len = -1;
	while (s1[++len])
		new_str[len] = s1[len];
	i = -1;
	while (s2[++i])
		new_str[len++] = s2[i];
	new_str[len] = '\0';
	return (new_str);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return ((char *)s + i);
	}
	if (c == 0)
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*str;

	len = 0;
	while (s[len])
		len++;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (len >= 0)
	{
		str[len] = s[len];
		len--;
	}
	return (str);
}
