/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:58:17 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/12 15:15:46 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_map_size(t_map *map, char *line)
{
	int	len;

	len = 0;
	map->height += 1;
	while (line[len])
		len++;
	if (len > map->width)
		map->width = len;
}

void	ft_clear_map(t_all *all, t_list **head)
{
	ft_lst_clear(head);
	ft_exit(all, -3, 1);
}

int		ft_parse_map(t_all *all, t_list **head)
{
	t_list	*tmp;
	int		i;

	if (!(all->map.map = (char **)calloc((ft_lstsize(*head) + 1),
		sizeof(char *))))
		ft_clear_map(all, head);
	i = -1;
	tmp = *head;
	while (tmp)
	{
		if (!(all->map.map[++i] = ft_strdup(tmp->content)))
			ft_clear_map(all, head);
		ft_map_size(&all->map, all->map.map[i]);
		tmp = tmp->next;
	}
	ft_lst_clear(head);
	ft_check_map(all);
	return (1);
}

int		ft_is_valid_map_value(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0'
			&& line[i] != '2' && line[i] != 'N' && line[i] != 'W'
			&& line[i] != 'S' && line[i] != 'E')
			return (0);
	}
	return (1);
}

int		ft_parse_map_line(t_all *all, char *line, t_list **head)
{
	static int	skiped_line;

	if ((*head) && ft_isemtyline(line))
		skiped_line = 1;
	else if (!ft_is_valid_map_value(line)
			|| (skiped_line && !ft_isemtyline(line)))
	{
		free(line);
		ft_lst_clear(head);
		ft_exit(all, -4, 1);
	}
	else if (!ft_isemtyline(line))
	{
		ft_lstadd_back(head, ft_lstnew(line));
		return (1);
	}
	free(line);
	return (0);
}
