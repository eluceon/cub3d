/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:51:32 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/11 17:18:29 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	ft_jump_player(t_all *all)
{
	static int jumped;
	static int up;

	if (!jumped)
	{
		jumped = 1;
		up = 1;
		all->win.half_height = all->win.height / 2;
		ft_draw_window(all);
	}
	if (up && (all->win.half_height + all->win.height * 0.08) < all->win.height)
		all->win.half_height += all->win.height * 0.08;
	else if (all->win.half_height > 0.5 * all->win.height)
	{
		up = 0;
		all->win.half_height -= all->win.height * 0.08;
	}
	if (up == 0 && (all->win.half_height > 0.4 * all->win.height
			&& all->win.half_height < 0.6 * all->win.height))
	{
		all->win.half_height = 0.5 * all->win.height;
		jumped = 0;
		all->keys.jump = 0;
	}
	return (1);
}
