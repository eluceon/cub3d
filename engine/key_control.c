/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 08:53:57 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/11 14:14:48 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int		ft_key_release(int key, t_all *all)
{
	if (key == ROTATE_RIGHT || key == KEY_RIGHT_LINUX)
		all->keys.rotate_right = 0;
	else if (key == ROTATE_LEFT || key == KEY_LEFT_LINUX)
		all->keys.rotate_left = 0;
	if (key == MOVE_FORWARD || key == KEY_W_LINUX)
		all->keys.forward = 0;
	else if (key == MOVE_BACKWARD || key == KEY_S_LINUX)
		all->keys.backward = 0;
	if (key == MOVE_RIGHT || key == KEY_D_LINUX)
		all->keys.right = 0;
	else if (key == MOVE_LEFT || key == KEY_A_LINUX)
		all->keys.left = 0;
	if (key == LOOK_UP || key == KEY_UP_LINUX)
		all->keys.look_up = 0;
	else if (key == LOOK_DOWN || key == KEY_DOWN_LINUX)
		all->keys.look_down = 0;
	return (0);
}

void	ft_key_press_end(int key, t_all *all)
{
	if (key == KEY_M || key == KEY_M_LINUX)
		all->settings = all->settings ^ FLAG_MINIMAP;
	else if (key == KEY_H || key == KEY_F1_LINUX)
		all->settings = all->settings ^ FLAG_HUD;
	else if (key == KEY_I || key == KEY_I_LINUX)
		all->settings = all->settings ^ FLAG_SHADOWS;
	else if (key == KEY_G || key == KEY_G_LINUX)
		all->settings = all->settings ^ FLAG_WEAPON;
	if (key == KEY_E || key == KEY_E_LINUX)
		ft_speed_up(&all->player.speed, all->keys.lie_down);
	else if (key == KEY_Q || key == KEY_Q_LINUX)
		ft_speed_down(&all->player.speed, all->keys.lie_down);
	if (key == KEY_L || key == KEY_L_LINUX)
		ft_lie_down(all);
	else if (key == KEY_K || key == KEY_K_LINUX)
		ft_stand_up(all);
	else if ((key == KEY_J || key == KEY_J_LINUX) && !all->keys.lie_down)
		all->keys.jump = 1;
	if (key == ESC || key == ESC_LINUX)
		ft_exit(all, 0, 0);
}

int		ft_key_press(int key, t_all *all)
{
	if (key == ROTATE_RIGHT || key == KEY_RIGHT_LINUX)
		all->keys.rotate_right = 1;
	else if (key == ROTATE_LEFT || key == KEY_LEFT_LINUX)
		all->keys.rotate_left = 1;
	if (key == MOVE_FORWARD || key == KEY_W_LINUX)
		all->keys.forward = 1;
	else if (key == MOVE_BACKWARD || key == KEY_S_LINUX)
		all->keys.backward = 1;
	if (key == MOVE_RIGHT || key == KEY_D_LINUX)
		all->keys.right = 1;
	else if (key == MOVE_LEFT || key == KEY_A_LINUX)
		all->keys.left = 1;
	if (key == LOOK_UP || key == KEY_UP_LINUX)
		all->keys.look_up = 1;
	else if (key == LOOK_DOWN || key == KEY_DOWN_LINUX)
		all->keys.look_down = 1;
	ft_key_press_end(key, all);
	return (0);
}
