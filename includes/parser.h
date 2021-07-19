/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:37:28 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/11 18:02:34 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include "utils.h"
# include "get_next_line.h"
# include "cub3d.h"

int	ft_parse_resolution(t_all *all, char *line, int i);
int	ft_path_texture(char *line, int i, t_texture *tex, void **mlx_ptr);
int	ft_parse_colors(char *line, int i, int *rgb);
int ft_parse_map(t_all *all, t_list **head);
int	ft_parse_map_line(t_all *all, char *line, t_list **head);
int	ft_check_map(t_all *all);

#endif
