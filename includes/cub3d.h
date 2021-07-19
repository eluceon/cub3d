/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 15:08:07 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/11 21:02:25 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>
# include <math.h>
# include "../minilibx_mms/mlx.h"
# include "utils.h"

# define FLAG_SAVE_BMP		0b00000001
# define FLAG_MINIMAP		0b00000010
# define FLAG_HUD			0b00000100
# define FLAG_SHADOWS		0b00001000
# define FLAG_WEAPON		0b00010000

# define TEXTURES			5
# define TEXTURES_BONUSES	8
# define TEX_NORTH			0
# define TEX_WEST			1
# define TEX_SOUTH			2
# define TEX_EAST			3
# define TEX_SPRITE			4
# define TEX_FLOOR			5
# define TEX_CEIL			6
# define TEX_WEAPON			7

# define MAX_WIN_WIDTH		8192
# define MAX_WIN_HEIGTH		4800

# define ERROR_EXIT			0
# define SUCCESS_EXIT		1

typedef struct	s_window
{
	void					*w_ptr;
	int						width;
	int						height;
	int						half_height;
}				t_window;

typedef struct	s_image {
	void					*img_ptr;
	char					*addr;
	int						bpp;
	int						line_size;
	int						endian;
}				t_image;

typedef struct	s_texture {
	void					*img_ptr;
	char					*addr;
	int						bpp;
	int						line_size;
	int						endian;
	int						width;
	int						height;
}				t_texture;

typedef struct	s_colors {
	int						floor;
	int						ceiling;
}				t_colors;

typedef struct	s_map {
	char					**map;
	int						width;
	int						height;
}				t_map;

typedef	struct	s_player
{
	double					pos_x;
	double					pos_y;
	double					plane_x;
	double					plane_y;
	double					dir_x;
	double					dir_y;
	double					speed;
	double					rotate_speed;
}				t_player;

typedef struct	s_ray
{
	double					dir_x;
	double					dir_y;
	int						map_x;
	int						map_y;
	double					perp_distance;
	double					side_dist_x;
	double					side_dist_y;
	double					delta_dist_x;
	double					delta_dist_y;
	int						step_x;
	int						step_y;
	int						side;
	double					z_buffer[MAX_WIN_WIDTH];
}				t_ray;

typedef struct	s_keys {
	int						forward;
	int						backward;
	int						left;
	int						right;
	int						rotate_right;
	int						rotate_left;
	int						look_up;
	int						look_down;
	int						lie_down;
	int						jump;
}				t_keys;

typedef struct	s_all
{
	int						settings;
	void					*mlx_ptr;
	t_keys					keys;
	t_ray					ray;
	t_window				win;
	t_image					img;
	t_texture				tex[TEXTURES_BONUSES];
	t_colors				color;
	t_map					map;
	t_player				player;
}				t_all;

typedef struct	s_map_list
{
	char					*content;
	struct s_map_list		*next;
}				t_map_list;

int				ft_parser(t_all *all, char *file);
void			ft_display(t_all *all);
int				ft_key_release(int key, t_all *all);
int				ft_key_press(int key, t_all *all);
int				ft_loop_control(t_all *all);
int				ft_close(t_all *all);
void			ft_free_parsed_data(t_all *all);
void			ft_draw_window(t_all *all);
void			ft_exit(t_all *all, int error_code, int exit_code);
void			ft_save_bitmap(t_all *all);

#endif
