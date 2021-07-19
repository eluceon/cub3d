/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 22:21:47 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/09 17:17:12 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int		ft_error_message(int error)
{
	(error == -1) ? write(2, "Error\n Can't open file\n", 23) : 0;
	(error == -2) ? write(2, "Error\n mlx_init() failed\n", 25) : 0;
	(error == -3) ? write(2, "Error\n Map malloc error\n", 24) : 0;
	(error == -4) ? write(2, "Error\n Invalid map\n", 19) : 0;
	(error == -5) ? write(2, "Error\n List sprite Malloc error\n", 32) : 0;
	(error == -6) ? write(2, "Error\n Few colors\n", 18) : 0;
	(error == -7) ? write(2, "Error\n Few textures\n", 20) : 0;
	(error == -8) ? write(2, "Error\n Can't open file (FD\n)", 28) : 0;
	(error == -9) ? write(2, "Error\n Can't parse file (GNL\n)", 30) : 0;
	(error == -10) ? write(2, "Error\n Can't parse map\n)", 24) : 0;
	(error == -11) ? write(2, "Error\n Duplicate resolution\n", 28) : 0;
	(error == -12) ? write(2, "Error\n Invalid resolution format\n", 33) : 0;
	(error == -13) ? write(2, "Error\n Duplicate texture\n", 25) : 0;
	(error == -14) ? write(2, "Error\n Invalid texture file path\n", 33) : 0;
	(error == -15) ? write(2, "Error\n Texture Malloc error\n", 28) : 0;
	(error == -16) ? write(2, "Error\n Duplicate floor/ceill colors\n", 36) : 0;
	(error == -17) ? write(2, "Error\n Invalid color format\n", 28) : 0;
	(error == -18) ? write(2, "Error\n Invalid texture file\n", 28) : 0;
	(error == -20) ? write(2, "Error\n Can't write header of bitmap\n", 36) : 0;
	(error == -21) ? write(2, "Error\n Can't write data into bitmap\n", 36) : 0;
	(error == -22) ? write(2, "Error\n Invalid map - no player\n", 31) : 0;
	return (1);
}

void	ft_exit(t_all *all, int error_code, int exit_code)
{
	ft_free_parsed_data(all);
	if (all->img.img_ptr && all->mlx_ptr)
		mlx_destroy_image(all->mlx_ptr, all->img.img_ptr);
	if (all->mlx_ptr && all->win.w_ptr)
		mlx_destroy_window(all->mlx_ptr, all->win.w_ptr);
	if (error_code < 0)
		ft_error_message(error_code);
	exit(exit_code);
}

int		ft_close(t_all *all)
{
	ft_exit(all, 0, 0);
	return (1);
}
