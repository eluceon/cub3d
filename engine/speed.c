/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:14:46 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/11 17:17:25 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	ft_lie_down(t_all *all)
{
	all->win.half_height = 0.05 * all->win.height;
	all->player.speed = 0.01;
	all->player.rotate_speed = 0.01;
	all->keys.lie_down = 1;
	ft_draw_window(all);
}

void	ft_stand_up(t_all *all)
{
	if (all->keys.lie_down)
	{
		all->win.half_height = 0.5 * all->win.height;
		all->player.speed = 0.03;
		all->player.rotate_speed = 0.04;
		all->keys.lie_down = 0;
		ft_draw_window(all);
	}
}

void	ft_speed_up(double *speed, int lie_down)
{
	if (*speed + 0.03 < 0.3 && lie_down == 0)
		*speed += 0.03;
}

void	ft_speed_down(double *speed, int lie_down)
{
	if (*speed - 0.03 > 0 && lie_down == 0)
		*speed -= 0.03;
}
