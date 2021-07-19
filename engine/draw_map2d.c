/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:34:45 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/10 15:05:26 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	ft_player(t_all *all, double x, double y, int color)
{
	int x_pos;
	int y_pos;

	x = all->win.width - WALL_WIDTH - WALL_WIDTH * all->map.width
		+ x * WALL_WIDTH;
	y = all->win.height - WALL_WIDTH - WALL_WIDTH * all->map.height
		+ y * WALL_WIDTH;
	y_pos = y - 3;
	while (y_pos++ < y + 3)
	{
		x_pos = x - 3;
		while (x_pos++ < x + 3)
			ft_put_pixel_to_image(all, x_pos, y_pos, color);
	}
}

void	ft_square(t_all *all, double x, double y, int color)
{
	int x_pos;
	int y_pos;

	x = all->win.width - WALL_WIDTH - WALL_WIDTH * all->map.width
		+ x * WALL_WIDTH;
	y = all->win.height - WALL_WIDTH - WALL_WIDTH * all->map.height
		+ y * WALL_WIDTH;
	y_pos = y;
	while (y_pos++ < y + WALL_WIDTH)
	{
		x_pos = x;
		while (x_pos++ < x + WALL_WIDTH)
			ft_put_pixel_to_image(all, x_pos, y_pos, color);
	}
}

void	ft_draw_map2d(t_all *all)
{
	int x;
	int y;

	y = -1;
	while (all->map.map[++y])
	{
		x = -1;
		while (all->map.map[y][++x])
		{
			if (all->map.map[y][x] == '1')
				ft_square(all, x, y, MAP_WALL_COLOR);
			else if (all->map.map[y][x] == '2')
				ft_square(all, x, y, MAP_SPRITE_COLOR);
			else if (all->map.map[y][x] == '0')
				ft_square(all, x, y, MAP_SPACE_COLOR);
		}
	}
	ft_player(all, all->player.pos_x, all->player.pos_y, PLAYER_COLOR);
}
