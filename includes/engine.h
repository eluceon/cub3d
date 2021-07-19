/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:50:40 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/11 17:58:24 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <fcntl.h>
# include "cub3d.h"

# define NORTH_SIDE			0
# define WEST_SIDE			1
# define SOUTH_SIDE			2
# define EAST_SIDE			3

# define PLAYER_COLOR		0x900FF00
# define MAP_SPACE_COLOR	0x00F0F0F0
# define MAP_WALL_COLOR		0x00303030
# define MAP_SPRITE_COLOR	0x00A00000
# define WALL_WIDTH			8

# define ESC				53
# define MOVE_LEFT 			0
# define MOVE_RIGHT			2
# define MOVE_FORWARD 		13
# define MOVE_BACKWARD		1
# define ROTATE_LEFT		123
# define ROTATE_RIGHT		124
# define LOOK_UP			126
# define LOOK_DOWN			125
# define KEY_M				46
# define KEY_J				38
# define KEY_I				34
# define KEY_G				5
# define KEY_L				37
# define KEY_Q				12
# define KEY_E				14
# define KEY_K				40
# define KEY_H				4

# define ESC_LINUX 			65307
# define KEY_A_LINUX 		97
# define KEY_D_LINUX 		100
# define KEY_W_LINUX 		119
# define KEY_S_LINUX 		115
# define KEY_LEFT_LINUX 	65361
# define KEY_RIGHT_LINUX	65363
# define KEY_UP_LINUX		65362
# define KEY_DOWN_LINUX		65364
# define KEY_M_LINUX		109
# define KEY_J_LINUX		106
# define KEY_L_LINUX		108
# define KEY_I_LINUX		105
# define KEY_Q_LINUX		113
# define KEY_E_LINUX		101
# define KEY_K_LINUX		107
# define KEY_F1_LINUX		65470
# define KEY_G_LINUX		103

typedef struct	s_pos
{
	double					x;
	double					y;
}				t_pos;

typedef struct	s_draw
{
	int						height;
	int						start;
	int						end;
}				t_draw;

typedef struct	s_floor
{
	t_pos					hor_ray_start;
	t_pos					hor_ray_end;
	double					vert_cam_pos;
	double					row_distance;
	double					step_x;
	double					step_y;
	double					x;
	double					y;
	t_pos					texture;
}				t_floor;

typedef struct	s_spr_lst
{
	double					pos_x;
	double					pos_y;
	double					distance;
	struct s_spr_lst		*next;
}				t_spr_lst;

typedef struct	s_sprite
{
	double					pos_x;
	double					pos_y;
	double					transform_x;
	double					transform_y;
	int						height;
	int						width;
	int						sprite_screen_x;
	int						draw_start_y;
	int						draw_end_y;
	int						draw_start_x;
	int						draw_end_x;

}				t_sprite;

void			ft_put_pixel_to_image(t_all *all, int x, int y, int color);
void			ft_draw_rectangle(t_all *all, t_pos start, t_pos end,
									int color);
int				ft_distance_shadow(int settings, double distance, int color);
void			ft_draw_player(t_all *all);
void			ft_draw_map2d(t_all *all);
int				ft_rotate_right (t_player *player);
int				ft_rotate_left (t_player *player);
int				ft_move_forward(char **map, t_player *player);
int				ft_move_left(char **map, t_player *player);
int				ft_move_backward(char **map, t_player *player);
int				ft_move_right(char **map, t_player *player);
int				ft_look_down(t_window *window);
int				ft_look_up(t_window *window);
void			ft_draw_window(t_all *all);
int				ft_get_pixel_from_img(t_texture texture, int x, int y);
void			ft_draw_wall(t_all *all, int x);
void			ft_draw_floor_ceiling(t_all *all);
void			ft_draw_sprites(t_all *all);
void			ft_lstclear_sprite(t_spr_lst**sprites);
void			ft_speed_down(double *speed, int lie_down);
void			ft_speed_up(double *speed, int lie_down);
void			ft_lie_down(t_all *all);
void			ft_stand_up(t_all *all);
void			ft_draw_weapon(t_all *all);
int				ft_jump_player(t_all *all);
void			ft_draw_hud(t_all *all);
void			ft_sort_spites(t_spr_lst **sprites, char **map, t_all *all);

#endif
