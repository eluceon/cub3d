/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 07:19:11 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/11 19:35:04 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** The function ft_load_texture() loads texture image from file. It returns 0
** if extension is not .xpm or img_ptr == NULL;
*/

int	ft_load_texture(t_texture *tex, char *path, void **mlx_ptr)
{
	if (!ft_check_extension(path, ".xpm"))
		return (0);
	tex->img_ptr = mlx_xpm_file_to_image(*mlx_ptr, path, &tex->width,
									&tex->height);
	if (!tex->img_ptr)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_size,
								&tex->endian);
	return (1);
}

/*
** The function ft_path_texture() parces path to the texture from map file.
*/

int	ft_path_texture(char *line, int i, t_texture *tex, void **mlx_ptr)
{
	int		j;
	char	*path;

	if (tex->addr)
		return (-13);
	i += 2;
	ft_skip_spaces(line, &i);
	j = i;
	while (line[j] && !ft_iswhitespace(line[j]))
		j++;
	ft_skip_spaces(line, &j);
	if (line[j])
		return (-14);
	if (!(path = (char *)malloc((j - i + 1) * sizeof(char))))
		return (-15);
	j = 0;
	while (line[i] && !ft_iswhitespace(line[i]))
		path[j++] = line[i++];
	path[j] = '\0';
	j = ft_load_texture(tex, path, mlx_ptr);
	free(path);
	if (j == 0)
		return (-18);
	free(line);
	return (1);
}

/*
** The function ft_parse_resolution() parces resolution from map file. If the
** declared screen size in the map is greater than the display resolution, the
** window size will be set depending to the current display resolution.
*/

int	ft_parse_resolution(t_all *all, char *line, int i)
{
	int	scr_width;
	int scr_height;

	if (all->win.width != 0 || all->win.height != 0)
		return (-11);
	++i;
	all->win.width = ft_atoi_cub(line, &i);
	all->win.height = ft_atoi_cub(line, &i);
	ft_skip_spaces(line, &i);
	mlx_get_screen_size(all->mlx_ptr, &scr_width, &scr_height);
	(all->win.width > scr_width) ? all->win.width = scr_width : 0;
	(all->win.height > scr_height) ? all->win.height = scr_height : 0;
	(all->win.width > MAX_WIN_WIDTH) ? all->win.width = MAX_WIN_WIDTH : 0;
	(all->win.height > MAX_WIN_HEIGTH) ? all->win.height = MAX_WIN_HEIGTH : 0;
	all->win.half_height = all->win.height / 2;
	if (line[i] || all->win.width <= 0 || all->win.height <= 0)
		return (-12);
	free(line);
	return (1);
}

/*
** The function ft_parse_colors() parces floor and ceiling colors from map
** file.
*/

int	ft_parse_colors(char *line, int i, int *rgb)
{
	int	r;
	int	g;
	int b;

	if (*rgb != -1)
		return (-16);
	++i;
	r = ft_atoi_cub(line, &i);
	ft_skip_spaces(line, &i);
	if (line[i++] != ',')
		return (-17);
	g = ft_atoi_cub(line, &(i));
	ft_skip_spaces(line, &i);
	if (line[i++] != ',')
		return (-17);
	b = ft_atoi_cub(line, &(i));
	ft_skip_spaces(line, &i);
	if (line[i] || r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-17);
	*rgb = (r << 16 | g << 8 | b);
	free(line);
	return (1);
}
