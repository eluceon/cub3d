/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 14:41:06 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/09 17:16:10 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_free_parsed_data(t_all *all)
{
	int	i;

	if (all->win.width == 0 || all->win.height == 0)
		ft_exit(all, -12, 1);
	i = -1;
	while (++i < TEXTURES_BONUSES)
	{
		if (all->tex[i].img_ptr)
			mlx_destroy_image(all->mlx_ptr, all->tex[i].img_ptr);
		all->tex[i].img_ptr = NULL;
		all->tex[i].addr = NULL;
	}
	i = -1;
	if (all->map.map)
	{
		while (all->map.map[++i])
		{
			free(all->map.map[i]);
			all->map.map[i] = NULL;
		}
		free(all->map.map);
		all->map.map = NULL;
	}
}

int		ft_check_line_error(t_all *all, char *line)
{
	int	i;

	i = -1;
	while (++i < TEXTURES_BONUSES)
	{
		if (!all->tex[i].img_ptr)
		{
			free(line);
			ft_exit(all, -7, 1);
		}
	}
	return (0);
}

int		ft_parse_manager(t_all *all, char *line, t_list **head, int i)
{
	if (ft_isemtyline(line) && !(*head))
		free(line);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		return (ft_parse_resolution(all, line, i));
	else if (line[i] == 'N' && line[i + 1] == 'O')
		return (ft_path_texture(line, i, &all->tex[TEX_NORTH], &all->mlx_ptr));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return (ft_path_texture(line, i, &all->tex[TEX_SOUTH], &all->mlx_ptr));
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (ft_path_texture(line, i, &all->tex[TEX_WEST], &all->mlx_ptr));
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (ft_path_texture(line, i, &all->tex[TEX_EAST], &all->mlx_ptr));
	else if (line[i] == 'S' && line[i + 1] == ' ')
		return (ft_path_texture(line, i, &all->tex[TEX_SPRITE], &all->mlx_ptr));
	else if (line[i] == 'F' && line[i + 1] == ' ')
		return (ft_path_texture(line, i, &all->tex[TEX_FLOOR], &all->mlx_ptr));
	else if (line[i] == 'C' && line[i + 1] == ' ')
		return (ft_path_texture(line, i, &all->tex[TEX_CEIL], &all->mlx_ptr));
	else if (line[i] == 'W' && line[i + 1] == ' ')
		return (ft_path_texture(line, i, &all->tex[TEX_WEAPON], &all->mlx_ptr));
	else if (!(ft_check_line_error(all, line)))
		ft_parse_map_line(all, line, head);
	return (0);
}

int		ft_parse_line(t_all *all, char *line, t_list **head)
{
	int i;
	int error;

	i = 0;
	error = 0;
	ft_skip_spaces(line, &i);
	error = ft_parse_manager(all, line, head, i);
	if (error < 0)
	{
		free(line);
		ft_exit(all, error, 1);
	}
	return (1);
}

int		ft_parser(t_all *all, char *file)
{
	int				fd;
	char			*line;
	int				i;
	t_list			*head;

	head = NULL;
	line = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_exit(all, -8, 1);
	while ((i = get_next_line(fd, &line)))
		ft_parse_line(all, line, &head);
	if (i == -1)
	{
		ft_lst_clear(&head);
		ft_exit(all, -9, 1);
	}
	ft_parse_map_line(all, line, &head);
	close(fd);
	if (!ft_parse_map(all, &head))
	{
		ft_lst_clear(&head);
		ft_exit(all, -10, 1);
	}
	return (0);
}
