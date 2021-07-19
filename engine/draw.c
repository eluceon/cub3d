/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:34:45 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/11 20:18:07 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	ft_put_pixel_to_image(t_all *all, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < all->win.width && y >= 0 && y < all->win.height)
	{
		dst = all->img.addr + (y * all->img.line_size + x * (all->img.bpp / 8));
		*(unsigned int*)dst = color;
	}
}

void	ft_draw_rectangle(t_all *all, t_pos start, t_pos end, int color)
{
	int x;
	int y;

	start.x = start.x < 0 ? 0 : start.x;
	start.y = start.y < 0 ? 0 : start.y;
	end.x = end.x >= all->win.width ? all->win.width - 1 : end.x;
	end.y = end.y >= all->win.height ? all->win.height - 1 : end.y;
	y = (int)start.y;
	while (y <= (int)end.y)
	{
		x = (int)start.x;
		while (x <= (int)end.x)
			ft_put_pixel_to_image(all, x++, y, color);
		y++;
	}
}

int		ft_distance_shadow(int settings, double distance, int color)
{
	distance /= 4;
	if (settings & FLAG_SHADOWS && distance > 1)
	{
		return ((((int)(((0xFF0000 & color) >> 16) / distance) << 16)
		+ ((int)(((0x00FF00 & color) >> 8) / distance) << 8)
		+ ((int)((0x0000FF & color) / distance))));
	}
	return (color);
}

int		ft_get_pixel_from_img(t_texture texture, int x, int y)
{
	if (x >= 0 && x < texture.width && y >= 0 && y < texture.height)
	{
		return (*(int*)(texture.addr + (y * texture.line_size + x
				* (texture.bpp / 8))));
	}
	return (0);
}
