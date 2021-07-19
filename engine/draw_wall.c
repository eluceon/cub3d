/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 07:07:07 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/09 08:29:40 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** The function ft_set_tex_position() finds x-coordinate of the texture.
** The value wall_hit_x represents the exact value where the wall was hit.
** The value tex_pos->x is coordinate on the texture.
*/

void	ft_set_tex_position(t_all *all, t_pos *tex_pos)
{
	double	wall_hit_x;

	if (all->ray.side == EAST_SIDE || all->ray.side == WEST_SIDE)
		wall_hit_x = all->player.pos_y + all->ray.perp_distance
					* all->ray.dir_y;
	else
		wall_hit_x = all->player.pos_x + all->ray.perp_distance
					* all->ray.dir_x;
	wall_hit_x -= floor((wall_hit_x));
	tex_pos->x = (int)(wall_hit_x * (double)all->tex[all->ray.side].width);
	if ((all->ray.side == EAST_SIDE || all->ray.side == WEST_SIDE)
			&& all->ray.dir_x > 0)
		tex_pos->x = all->tex[all->ray.side].width - tex_pos->x - 1;
	if ((all->ray.side == NORTH_SIDE || all->ray.side == SOUTH_SIDE)
			&& all->ray.dir_y < 0)
		tex_pos->x = all->tex[all->ray.side].width - tex_pos->x - 1;
}

/*
** The function ft_draw_wall() draws the wall.
** draw.height - the height of the wall line.
** step - how much to increase the texture coordinate per screen pixel.
** The value tex_pos->x is coordinate on the texture.
*/

void	ft_draw_wall(t_all *all, int x)
{
	t_draw	draw;
	double	t_pos_double;
	double	step;
	t_pos	tex_pos;

	draw.height = (int)(all->win.height / all->ray.perp_distance);
	draw.start = all->win.half_height - draw.height / 2;
	draw.start = draw.start < 0 ? 0 : draw.start;
	draw.end = all->win.half_height + draw.height / 2;
	draw.end = draw.end > all->win.height - 1 ? all->win.height - 1 : draw.end;
	ft_set_tex_position(all, &tex_pos);
	step = 1.0 * all->tex[all->ray.side].height / draw.height;
	t_pos_double = (draw.start - all->win.half_height + draw.height / 2) * step;
	while (draw.start < draw.end)
	{
		tex_pos.y = (int)t_pos_double;
		t_pos_double += step;
		ft_put_pixel_to_image(all, x, draw.start++,
			ft_distance_shadow(all->settings, all->ray.perp_distance,
			ft_get_pixel_from_img(all->tex[all->ray.side],
									tex_pos.x, tex_pos.y)));
	}
}
