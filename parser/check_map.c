/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 12:54:52 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/12 15:14:19 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_set_value_to_zero(double *n1, double *n2)
{
	*n1 = 0;
	*n2 = 0;
}

void	ft_player_direction(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->dir_y = -1;
		player->plane_x = 0.58;
		ft_set_value_to_zero(&player->dir_x, &player->plane_y);
	}
	else if (direction == 'W')
	{
		player->dir_x = -1;
		player->plane_y = -0.58;
		ft_set_value_to_zero(&player->dir_y, &player->plane_x);
	}
	else if (direction == 'E')
	{
		player->dir_x = 1;
		player->plane_y = 0.58;
		ft_set_value_to_zero(&player->dir_y, &player->plane_x);
	}
	else if (direction == 'S')
	{
		player->dir_y = 1;
		player->plane_x = -0.58;
		ft_set_value_to_zero(&player->dir_x, &player->plane_y);
	}
}

void	ft_check_spaces(t_all *all, t_map map, int i, int j)
{
	int	near[2];

	if (map.map[i][j] == '0' || map.map[i][j] == '2')
	{
		if (i - 1 < 0 || j - 1 < 0 || !map.map[i + 1]
			|| ft_strlen(map.map[i - 1]) < j + 1
			|| ft_strlen(map.map[i + 1]) < j + 1)
			ft_exit(all, -4, 1);
		near[0] = -2;
		while (++near[0] <= 1)
		{
			near[1] = -2;
			while (++near[1] <= 1)
			{
				if (ft_iswhitespace(map.map[i + near[0]][j + near[1]])
					|| map.map[i + near[0]][j + near[1]] == '\0')
					ft_exit(all, -4, 1);
			}
		}
	}
}

void	ft_check_player(t_all *all, t_map *map, int i, int j)
{
	int	near[2];

	if (map->map[i][j] == 'N' || map->map[i][j] == 'W'
		|| map->map[i][j] == 'S' || map->map[i][j] == 'E')
	{
		if (all->player.pos_y >= 0 || i - 1 < 0 || j - 1 < 0
			|| !map->map[i + 1] || ft_strlen(map->map[i - 1]) < j + 1
			|| ft_strlen(map->map[i + 1]) < j + 1)
			ft_exit(all, -4, 1);
		all->player.pos_y = i + 0.5;
		all->player.pos_x = j + 0.5;
		ft_player_direction(&all->player, map->map[i][j]);
		near[0] = -2;
		while (++near[0] <= 1)
		{
			near[1] = -2;
			while (++near[1] <= 1)
			{
				if (ft_iswhitespace(map->map[i + near[0]][j + near[1]])
					|| map->map[i + near[0]][j + near[1]] == '\0')
					ft_exit(all, -4, 1);
			}
		}
		map->map[i][j] = '0';
	}
}

int		ft_check_map(t_all *all)
{
	int	i;
	int	j;

	i = -1;
	while (all->map.map[++i])
	{
		j = -1;
		while (all->map.map[i][++j])
		{
			ft_check_player(all, &all->map, i, j);
			ft_check_spaces(all, all->map, i, j);
		}
	}
	if (all->player.pos_y == -1)
		ft_exit(all, -22, 1);
	return (1);
}
