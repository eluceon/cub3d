/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:30:07 by eluceon           #+#    #+#             */
/*   Updated: 2020/12/28 11:04:10 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_and_null(char **str)
{
	if (str)
	{
		free(*str);
		*str = NULL;
	}
}

int		ft_return(int n_read, char **line, char *p_nl, char **remainder)
{
	if (n_read < 0 || !(*line))
	{
		free_and_null(remainder);
		free_and_null(line);
		return (-1);
	}
	else if (n_read || p_nl)
		return (1);
	else
	{
		free_and_null(remainder);
		return (0);
	}
}

/*
** The function checks for a remainder. If the remainder exists then function
** checks for a line break. If the remainder does not exist or there is no
** line break in the remainder then find_remainder returns NULL.
*/

char	*find_remainder(char **line, char *remainder)
{
	char	*p_nl;

	p_nl = NULL;
	if (remainder)
	{
		if ((p_nl = ft_strchr(remainder, '\n')))
		{
			*p_nl = '\0';
			*line = ft_strdup(remainder);
			remainder = ft_strcpy(remainder, ++p_nl);
		}
		else
		{
			*line = ft_strdup(remainder);
			remainder[0] = '\0';
		}
	}
	else
	{
		if ((*line = (char *)malloc(sizeof(char))))
			*line[0] = '\0';
	}
	return (p_nl);
}

/*
** The function checks for a line break in buffer during reading. If there is
** no line break in the buffer then function returns NULL.
*/

char	*newline_in_buffer(char *buffer, char **remainder)
{
	char	*p_nl;

	p_nl = NULL;
	if ((p_nl = ft_strchr(buffer, '\n')))
	{
		*p_nl = '\0';
		free_and_null(remainder);
		*remainder = ft_strdup(++p_nl);
	}
	return (p_nl);
}

int		get_next_line(int fd, char **line)
{
	int			n_read;
	char		buffer[BUFFER_SIZE + 1];
	static char	*remainder;
	char		*p_nl;
	char		*tmp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	p_nl = find_remainder(line, remainder);
	if (!(*line))
	{
		free_and_null(&remainder);
		return (-1);
	}
	n_read = 0;
	while (!p_nl && (n_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[n_read] = '\0';
		p_nl = newline_in_buffer(buffer, &remainder);
		tmp = *line;
		*line = ft_strjoin(*line, buffer);
		free(tmp);
	}
	return (ft_return(n_read, line, p_nl, &remainder));
}
