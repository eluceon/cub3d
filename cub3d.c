/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 15:00:20 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/11 13:12:18 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_settings(t_all *all)
{
	int	i;

	all->settings = 0b00000000;
	all->player.speed = 0.03;
	all->player.rotate_speed = 0.04;
	all->keys.forward = 0;
	all->keys.backward = 0;
	all->keys.left = 0;
	all->keys.right = 0;
	all->keys.rotate_left = 0;
	all->keys.rotate_right = 0;
	all->keys.look_up = 0;
	all->keys.look_down = 0;
	all->keys.lie_down = 0;
	all->keys.jump = 0;
	all->player.pos_y = -1;
	all->player.pos_x = -1;
	i = -1;
	while (++i < TEXTURES_BONUSES)
	{
		all->tex[i].addr = NULL;
		all->tex[i].img_ptr = NULL;
	}
}

void	init_game(t_all *all, char *file, int save_bmp)
{
	ft_init_settings(all);
	all->color.floor = -1;
	all->color.ceiling = -1;
	all->map.map = NULL;
	all->map.height = 0;
	all->map.width = 0;
	all->win.height = 0;
	all->win.width = 0;
	all->win.w_ptr = NULL;
	all->img.img_ptr = NULL;
	if (!(all->mlx_ptr = mlx_init()))
		ft_exit(all, -2, 1);
	ft_parser(all, file);
	all->img.img_ptr = mlx_new_image(all->mlx_ptr, all->win.width,
										all->win.height);
	all->img.addr = mlx_get_data_addr(all->img.img_ptr, &all->img.bpp,
										&all->img.line_size, &all->img.endian);
	if (save_bmp)
		all->settings = all->settings | save_bmp;
	else
		all->win.w_ptr = mlx_new_window(all->mlx_ptr, all->win.width,
											all->win.height, "Cub3D");
}

int		ft_error_input(int argc, char **argv)
{
	if ((argc == 2 || argc == 3) && !(ft_check_extension(argv[1], ".cub")))
		write(2, "Error\n Invalid map file name\n", 29);
	else if (argc == 1)
		write(2, "Error\n Enter an argument with a map file name\n", 46);
	else if (argc > 3)
		write(2, "Error\n Too many arguments\n", 26);
	else
		write(2, "Error\n Invalid arguments\n", 25);
	return (1);
}

int		main(int argc, char **argv)
{
	t_all	all;

	if (argc == 2 && ft_check_extension(argv[1], ".cub"))
		init_game(&all, argv[1], 0);
	else if (argc == 3 && (ft_strcmp(argv[2], "--save") == 0)
				&& ft_check_extension(argv[1], ".cub"))
		init_game(&all, argv[1], 1);
	else
		return (ft_error_input(argc, argv));
	ft_draw_window(&all);
	if (all.settings & FLAG_SAVE_BMP)
		ft_save_bitmap(&all);
	mlx_hook(all.win.w_ptr, 2, 1L << 0, ft_key_press, &all);
	mlx_hook(all.win.w_ptr, 3, 1L << 1, ft_key_release, &all);
	mlx_hook(all.win.w_ptr, 17, 0, ft_close, &all);
	mlx_loop_hook(all.mlx_ptr, ft_loop_control, &all);
	mlx_loop(all.mlx_ptr);
	return (0);
}
