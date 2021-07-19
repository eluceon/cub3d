/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bitmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:31:04 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/11 20:25:49 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int		ft_bitmap_file_header(int fd, int file_size)
{
	int				i;
	unsigned char	bitmap_file_header[14];

	i = -1;
	while (++i < 14)
		bitmap_file_header[i] = (unsigned char)0;
	bitmap_file_header[0] = (unsigned char)0x42;
	bitmap_file_header[1] = (unsigned char)0x4D;
	bitmap_file_header[2] = (unsigned char)(file_size & 0x0000FF);
	bitmap_file_header[3] = (unsigned char)((file_size & 0x00FF00) >> 8);
	bitmap_file_header[4] = (unsigned char)((file_size & 0xFF0000) >> 16);
	bitmap_file_header[5] = (unsigned char)((file_size & 0xFF000000) >> 24);
	bitmap_file_header[10] = (unsigned char)(14 + 40);
	return (write(fd, bitmap_file_header, 14));
}

int		ft_bitmap_info_header(int fd, int img_width, int img_height, int bpp)
{
	int				i;
	unsigned char	bitmap_info_header[40];

	i = -1;
	while (++i < 40)
		bitmap_info_header[i] = (unsigned char)0;
	bitmap_info_header[0] = (unsigned char)40;
	bitmap_info_header[4] = (unsigned char)(img_width & 0x0000FF);
	bitmap_info_header[5] = (unsigned char)((img_width & 0x00FF00) >> 8);
	bitmap_info_header[6] = (unsigned char)((img_width & 0xFF0000) >> 16);
	bitmap_info_header[7] = (unsigned char)((img_width & 0xFF000000) >> 24);
	bitmap_info_header[8] = (unsigned char)(img_height & 0x0000FF);
	bitmap_info_header[9] = (unsigned char)((img_height & 0x00FF00) >> 8);
	bitmap_info_header[10] = (unsigned char)((img_height & 0xFF0000) >> 16);
	bitmap_info_header[11] = (unsigned char)((img_height & 0xFF000000) >> 24);
	bitmap_info_header[12] = (unsigned char)1;
	bitmap_info_header[14] = (unsigned char)(bpp);
	return (write(fd, bitmap_info_header, 40));
}

void	ft_pixel_data(t_all *all, int fd)
{
	int	i;
	int	j;
	int tmp;

	i = all->img.line_size * (all->win.height - 1);
	while (i >= 0)
	{
		j = -1;
		tmp = i - all->img.line_size;
		while (++j < all->win.width * 4)
		{
			if (write(fd, &all->img.addr[i++], 1) < 0)
			{
				close(fd);
				ft_exit(all, -21, 1);
			}
		}
		i = tmp;
	}
}

void	ft_save_bitmap(t_all *all)
{
	int	fd;
	int file_size;

	if (!(fd = open("cub3D.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)))
		ft_exit(all, -19, 1);
	file_size = 14 + 40 + 4 * all->win.width * all->win.height;
	if ((ft_bitmap_file_header(fd, file_size) <= 0))
	{
		close(fd);
		ft_exit(all, -20, 1);
	}
	if ((ft_bitmap_info_header(fd, all->win.width, all->win.height,
								all->img.bpp) <= 0))
	{
		close(fd);
		ft_exit(all, -20, 1);
	}
	ft_pixel_data(all, fd);
	close(fd);
	ft_exit(all, 0, 0);
}
