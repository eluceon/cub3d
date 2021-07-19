/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 22:00:01 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/07 15:58:06 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** The function ft_texture_init() calculates data for texture.
** hor_ray_start is horisontal start position of the ray, leftmost ray.
** hor_ray_end is horisontal end position of the ray, rightmost ray.
** vert_cam_pos is vertical position of the camera.
** row_distance is horizontal distance from the camera to the floor.
** for the current row.
** floor->step_x is real world step.
** floor->x and floor->y are real world coordinates of the leftmost column.
** This coordinates will be updated as we step to the right.
*/

void	ft_texture_init(t_all *all, t_floor *floor, int y)
{
	floor->hor_ray_start.x = all->player.dir_x - all->player.plane_x;
	floor->hor_ray_start.y = all->player.dir_y - all->player.plane_y;
	floor->hor_ray_end.x = all->player.dir_x + all->player.plane_x;
	floor->hor_ray_end.y = all->player.dir_y + all->player.plane_y;
	floor->vert_cam_pos = all->win.height / 2;
	if (y - all->win.half_height != 0)
		floor->row_distance =
						fabs(floor->vert_cam_pos / (y - all->win.half_height));
	else
		floor->row_distance = floor->vert_cam_pos;
	floor->step_x = (floor->hor_ray_end.x - floor->hor_ray_start.x)
					* floor->row_distance / all->win.width;
	floor->step_y = (floor->hor_ray_end.y - floor->hor_ray_start.y)
					* floor->row_distance / all->win.width;
	floor->x = all->player.pos_x + floor->row_distance * floor->hor_ray_start.x;
	floor->y = all->player.pos_y + floor->row_distance * floor->hor_ray_start.y;
}

void	ft_draw_floor_texture(t_all *all, t_floor *floor, int y)
{
	int x;

	x = -1;
	while (++x < all->win.width)
	{
		floor->texture.x = (int)(all->tex[TEX_FLOOR].width
							* (floor->x - (int)(floor->x)));
		floor->texture.y = (int)(all->tex[TEX_FLOOR].height
							* (floor->y - (int)(floor->y)));
		floor->x += floor->step_x;
		floor->y += floor->step_y;
		ft_put_pixel_to_image(all, x, y,
			ft_distance_shadow(all->settings, floor->row_distance,
			ft_get_pixel_from_img(all->tex[TEX_FLOOR],
							floor->texture.x, floor->texture.y)));
	}
}

void	ft_draw_ceiling_texture(t_all *all, t_floor *floor, int y)
{
	int x;

	x = -1;
	while (++x < all->win.width)
	{
		floor->texture.x = (int)(all->tex[TEX_CEIL].width
							* (floor->x - (int)(floor->x)));
		floor->texture.y = (int)(all->tex[TEX_CEIL].height
							* (floor->y - (int)(floor->y)));
		floor->x += floor->step_x;
		floor->y += floor->step_y;
		ft_put_pixel_to_image(all, x, y,
					ft_distance_shadow(all->settings, floor->row_distance,
					ft_get_pixel_from_img(all->tex[TEX_CEIL],
									floor->texture.x, floor->texture.y)));
	}
}

void	ft_draw_texture_floor(t_all *all)
{
	t_floor	floor;
	int		y;

	y = -1;
	while (++y < all->win.height)
	{
		ft_texture_init(all, &floor, y);
		if (y > all->win.half_height)
			ft_draw_floor_texture(all, &floor, y);
		else
			ft_draw_ceiling_texture(all, &floor, y);
	}
}

void	ft_draw_floor_ceiling(t_all *all)
{
	t_pos start;
	t_pos end;

	if (all->tex[TEX_FLOOR].addr)
	{
		ft_draw_texture_floor(all);
		return ;
	}
	start.x = 0;
	start.y = 0;
	end.x = all->win.width - 1;
	end.y = all->win.half_height;
	ft_draw_rectangle(all, start, end, all->color.floor);
	start.y = all->win.half_height + 1;
	end.y = all->win.height - 1;
	ft_draw_rectangle(all, start, end, all->color.ceiling);
}
