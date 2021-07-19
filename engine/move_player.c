/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:52:40 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/11 17:19:56 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	ft_move_forward(char **map, t_player *player)
{
	if (map[(int)(player->pos_y + player->dir_y * player->speed)]
				[(int)(player->pos_x)] == '0')
	{
		player->pos_y += player->dir_y * player->speed;
	}
	if (map[(int)(player->pos_y)]
				[(int)(player->pos_x + player->dir_x * player->speed)] == '0')
	{
		player->pos_x += player->dir_x * player->speed;
	}
	return (1);
}

int	ft_move_backward(char **map, t_player *player)
{
	if (map[(int)(player->pos_y - player->dir_y * player->speed)]
				[(int)(player->pos_x)] == '0')
	{
		player->pos_y -= player->dir_y * player->speed;
	}
	if (map[(int)(player->pos_y)]
				[(int)(player->pos_x - player->dir_x * player->speed)] == '0')
	{
		player->pos_x -= player->dir_x * player->speed;
	}
	return (1);
}

int	ft_move_left(char **map, t_player *player)
{
	if (map[(int)player->pos_y]
			[(int)(player->pos_x - player->plane_x * player->speed)] == '0')
	{
		player->pos_x -= player->plane_x * player->speed;
	}
	if (map[(int)(player->pos_y - player->plane_y * player->speed)]
			[(int)player->pos_x] == '0')
	{
		player->pos_y -= player->plane_y * player->speed;
	}
	return (1);
}

int	ft_move_right(char **map, t_player *player)
{
	if (map[(int)player->pos_y]
			[(int)(player->pos_x + player->plane_x * player->speed)] == '0')
	{
		player->pos_x += player->plane_x * player->speed;
	}
	if (map[(int)(player->pos_y + player->plane_y * player->speed)]
			[(int)player->pos_x] == '0')
	{
		player->pos_y += player->plane_y * player->speed;
	}
	return (1);
}
