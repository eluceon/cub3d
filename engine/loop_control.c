/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:45:36 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/11 14:27:35 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	ft_loop_control_update(t_all *all, int update)
{
	static int	last_settings;

	if (last_settings != all->settings)
	{
		update = 1;
		last_settings = all->settings;
	}
	if (update)
		ft_draw_window(all);
}

int		ft_loop_control(t_all *all)
{
	int			update;

	update = 0;
	if (all->keys.rotate_left)
		update = ft_rotate_left(&all->player);
	else if (all->keys.rotate_right)
		update = ft_rotate_right(&all->player);
	if (all->keys.forward)
		update = ft_move_forward(all->map.map, &all->player);
	else if (all->keys.backward)
		update = ft_move_backward(all->map.map, &all->player);
	if (all->keys.right)
		update = ft_move_right(all->map.map, &all->player);
	else if (all->keys.left)
		update = ft_move_left(all->map.map, &all->player);
	if (all->keys.look_up)
		update = ft_look_down(&all->win);
	else if (all->keys.look_down)
		update = ft_look_up(&all->win);
	if (all->keys.jump)
		update = ft_jump_player(all);
	ft_loop_control_update(all, update);
	return (1);
}
