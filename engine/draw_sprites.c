/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 03:00:46 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/10 14:37:00 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** The function ft_calculate_sprite() calculates data for drawing sprites.
** sprite->pos_x and sprite->pos_y are sprite position to relative to camera.
*/

void	ft_calculate_sprite(t_all *all, t_spr_lst *spr_lst, t_sprite *sprite,
							double inv_det)
{
	sprite->pos_x = spr_lst->pos_x - all->player.pos_x;
	sprite->pos_y = spr_lst->pos_y - all->player.pos_y;
	sprite->transform_x = inv_det * (all->player.dir_y * sprite->pos_x
							- all->player.dir_x * sprite->pos_y);
	sprite->transform_y = inv_det * (-all->player.plane_y * sprite->pos_x
							+ all->player.plane_x * sprite->pos_y);
	sprite->sprite_screen_x = (int)((all->win.width / 2)
							* (1 + sprite->transform_x / sprite->transform_y));
	sprite->height = abs((int)(all->win.height / (sprite->transform_y)));
	sprite->draw_start_y = -sprite->height / 2 + all->win.half_height;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	sprite->draw_end_y = sprite->height / 2 + all->win.half_height;
	if (sprite->draw_end_y >= all->win.height)
		sprite->draw_end_y = all->win.height - 1;
	sprite->width = abs((int)(all->win.height / (sprite->transform_y)));
	sprite->draw_start_x = -sprite->width / 2 + sprite->sprite_screen_x;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	sprite->draw_end_x = sprite->width / 2 + sprite->sprite_screen_x;
	if (sprite->draw_end_x >= all->win.width)
		sprite->draw_end_x = all->win.width - 1;
}

void	ft_draw_pixel_in_stripe(t_all *all, int stripe, t_sprite spr, int tex_x)
{
	int		color;
	int		tex_y;
	int		y;
	int		d;

	y = spr.draw_start_y;
	while (y < spr.draw_end_y)
	{
		d = (y) - all->win.half_height + spr.height / 2;
		tex_y = ((d * all->tex[TEX_SPRITE].height) / spr.height);
		color = ft_get_pixel_from_img(all->tex[TEX_SPRITE], tex_x, tex_y);
		if (color != 0)
			ft_put_pixel_to_image(all, stripe, y,
						ft_distance_shadow(all->settings, fabs(spr.transform_y),
						color));
		y++;
	}
}

void	ft_draw_sprite(t_all *all, t_sprite sprite)
{
	int		stripe;
	int		tex_x;

	stripe = sprite.draw_start_x;
	while (stripe < sprite.draw_end_x)
	{
		tex_x = (int)((stripe - (-sprite.width / 2
		+ sprite.sprite_screen_x)) * all->tex[TEX_SPRITE].width / sprite.width);
		if (sprite.transform_y > 0 && stripe > 0 && stripe < all->win.width
			&& sprite.transform_y < all->ray.z_buffer[stripe])
		{
			ft_draw_pixel_in_stripe(all, stripe, sprite, tex_x);
		}
		stripe++;
	}
}

void	ft_draw_sprites(t_all *all)
{
	t_spr_lst	*spr_lst;
	t_spr_lst	*tmp_lst;
	t_sprite	sprite;
	double		inv_det;

	spr_lst = NULL;
	ft_sort_spites(&spr_lst, all->map.map, all);
	inv_det = 1.0 / (all->player.plane_x * all->player.dir_y
				- all->player.dir_x * all->player.plane_y);
	tmp_lst = spr_lst;
	while (spr_lst)
	{
		ft_calculate_sprite(all, spr_lst, &sprite, inv_det);
		ft_draw_sprite(all, sprite);
		spr_lst = spr_lst->next;
	}
	ft_lstclear_sprite(&tmp_lst);
}
