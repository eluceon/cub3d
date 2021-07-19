/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:57:09 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/11 15:41:53 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** The function ft_calculate_side_delta_distance() finds delta_dist_x and
** delta_dist_y - the distance the ray has to travel to go from 1 x-side to
** the next x-side, or from 1 y-side to the next y-side. The DDA algorithm
** will always jump exactly one square each loop, either a square in the
** x-direction, or a square in the y-direction. If it has to go in the negative
** or positive x-direction, and the negative or positive y-direction will
** depend on the direction of the ray, and this fact will be stored in step_x
** and step_y. Those variables are always either -1 or +1.
*/

void	ft_calculate_side_delta_distance(t_ray *ray, t_player *player)
{
	ray->delta_dist_x = (ray->dir_x == 0) ? 100000000.0 : fabs(1 / ray->dir_x);
	ray->delta_dist_y = (ray->dir_y == 0) ? 100000000.0 : fabs(1 / ray->dir_y);
	if (ray->dir_x < 0)
	{
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
		ray->step_x = -1;
	}
	else
	{
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
							* ray->delta_dist_x;
		ray->step_x = 1;
	}
	if (ray->dir_y < 0)
	{
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
		ray->step_y = -1;
	}
	else
	{
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
							* ray->delta_dist_y;
		ray->step_y = 1;
	}
}

void	ft_check_ray_hit_wall(t_ray *ray, t_map map)
{
	while ((map.map[ray->map_y][ray->map_x] != '1'))
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 2 + ray->step_x;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1 + ray->step_y;
		}
	}
}

/*
** camera_x is the x-coordinate on the camera plane that the current
** x-coordinate of the screen represents, done this way so that the right
** side of the screen will get coordinate 1, the center of the screen gets
** coordinate 0, and the left side of the screen gets coordinate -1.
*/

void	ft_ray_position_direction(t_all *all, double x)
{
	double camera_x;

	camera_x = 2 * x / (double)all->win.width - 1;
	all->ray.dir_x = all->player.dir_x + all->player.plane_x * camera_x;
	all->ray.dir_y = all->player.dir_y + all->player.plane_y * camera_x;
	all->ray.map_x = (int)all->player.pos_x;
	all->ray.map_y = (int)all->player.pos_y;
}

/*
** The function ft_ray_position_direction() calculates perpendicular distance
** from the player's camera plane to the wall hitpoint.
** (1 - ray->step_x) / 2 is 1 if step_x = -1 and 0 if step_x is +1, this is
** needed because we need to add 1 to the length when ray.dir_y < 0.
*/

void	ft_calculate_perp_distance(t_ray *ray, t_player plr)
{
	if (ray->side == EAST_SIDE || ray->side == WEST_SIDE)
		ray->perp_distance = (ray->map_x - plr.pos_x + (1 - ray->step_x) / 2)
								/ ray->dir_x;
	else
		ray->perp_distance = (ray->map_y - plr.pos_y + (1 - ray->step_y) / 2)
								/ ray->dir_y;
}

void	ft_draw_window(t_all *all)
{
	int x;

	ft_draw_floor_ceiling(all);
	x = -1;
	while (++x < all->win.width)
	{
		ft_ray_position_direction(all, (double)x);
		ft_calculate_side_delta_distance(&all->ray, &all->player);
		ft_check_ray_hit_wall(&all->ray, all->map);
		ft_calculate_perp_distance(&all->ray, all->player);
		all->ray.z_buffer[x] = all->ray.perp_distance;
		ft_draw_wall(all, x);
	}
	ft_draw_sprites(all);
	if (all->settings & FLAG_MINIMAP)
		ft_draw_map2d(all);
	if (all->settings & FLAG_WEAPON)
		ft_draw_weapon(all);
	if (all->settings & FLAG_SAVE_BMP)
		return ;
	mlx_put_image_to_window(all->mlx_ptr, all->win.w_ptr,
							all->img.img_ptr, 0, 0);
	if (all->settings & FLAG_HUD)
		ft_draw_hud(all);
	mlx_do_sync(all->mlx_ptr);
}
