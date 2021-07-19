/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 20:55:38 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/10 15:55:34 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	ft_draw_hud(t_all *all)
{
	if (all->win.height >= 200 && all->win.width >= 450)
	{
		mlx_string_put(all->mlx_ptr, all->win.w_ptr, 10, 20, 0xffffff,
		"F1 - help hud, M - minimap, I - shadows, ESC - leave game");
		mlx_string_put(all->mlx_ptr, all->win.w_ptr, 10, 40, 0xffffff,
		"W - forwads, S - backward, E - speed up, Q - speed down");
		mlx_string_put(all->mlx_ptr, all->win.w_ptr, 10, 60, 0xffffff,
		"J - jump, L - lay down, A - left, D - Right, K - stand up, G - gun");
		mlx_string_put(all->mlx_ptr, all->win.w_ptr, 10, 80, 0xffffff,
		"/\\ - look up , \\/ - look down,  < - rotate left, > - rotate right");
	}
}
