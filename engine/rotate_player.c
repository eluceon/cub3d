/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:52:56 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/11 14:37:08 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	ft_rotate_right(t_player *player)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(player->rotate_speed)
						- player->dir_y * sin(player->rotate_speed);
	player->dir_y = old_dir_x * sin(player->rotate_speed)
						+ player->dir_y * cos(player->rotate_speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(player->rotate_speed)
						- player->plane_y * sin(player->rotate_speed);
	player->plane_y = old_plane_x * sin(player->rotate_speed)
						+ player->plane_y * cos(player->rotate_speed);
	return (1);
}

int	ft_rotate_left(t_player *player)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(-player->rotate_speed)
						- player->dir_y * sin(-player->rotate_speed);
	player->dir_y = old_dir_x * sin(-player->rotate_speed)
						+ player->dir_y * cos(-player->rotate_speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(-player->rotate_speed)
						- player->plane_y * sin(-player->rotate_speed);
	player->plane_y = old_plane_x * sin(-player->rotate_speed)
						+ player->plane_y * cos(-player->rotate_speed);
	return (1);
}

int	ft_look_up(t_window *window)
{
	if ((window->half_height - 0.03 * window->height) > 0)
		window->half_height -= 0.03 * window->height;
	return (1);
}

int	ft_look_down(t_window *window)
{
	if ((window->half_height + 0.03 * window->height) < window->height)
		window->half_height += 0.03 * window->height;
	return (1);
}
