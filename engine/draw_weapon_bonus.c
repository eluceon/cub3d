/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:08:24 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/10 15:56:23 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	ft_draw_weapon(t_all *all)
{
	int		color;
	t_pos	screen;
	t_pos	ctr;

	if (all->win.height >= 200 && all->win.width >= 200)
	{
		ctr.y = -1;
		while (++ctr.y < all->tex[TEX_WEAPON].height)
		{
			ctr.x = -1;
			while (++ctr.x < all->tex[TEX_WEAPON].width)
			{
				color = ft_get_pixel_from_img(all->tex[TEX_WEAPON],
												ctr.x, ctr.y);
				screen.x = ctr.x + all->win.width / 2
							- all->tex[TEX_WEAPON].width / 2;
				screen.y = ctr.y + all->win.height
							- all->tex[TEX_WEAPON].height;
				if (color != 0x00ff00)
					ft_put_pixel_to_image(all, screen.x, screen.y, color);
			}
		}
	}
}
