/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 04:15:09 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/10 14:58:30 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void		ft_lstclear_sprite(t_spr_lst **sprites)
{
	t_spr_lst	*tmp1;
	t_spr_lst	*tmp2;

	if (*sprites)
	{
		tmp1 = *sprites;
		while (tmp1)
		{
			tmp2 = tmp1->next;
			free(tmp1);
			tmp1 = tmp2;
		}
		*sprites = NULL;
	}
}

t_spr_lst	*ft_lstnew_sprite(t_player player, t_pos sp_pos, t_all *all,
								t_spr_lst **sprites)
{
	t_spr_lst	*new;

	if (!(new = (t_spr_lst*)malloc(sizeof(t_spr_lst))))
	{
		ft_lstclear_sprite(sprites);
		ft_exit(all, -5, 1);
	}
	new->next = NULL;
	new->pos_y = sp_pos.y;
	new->pos_x = sp_pos.x;
	new->distance = (player.pos_y - sp_pos.y) * (player.pos_y - sp_pos.y)
					+ (player.pos_x - sp_pos.x) * (player.pos_x - sp_pos.x);
	return (new);
}

t_spr_lst	*ft_sort_lst_sprites(t_spr_lst **sprites, t_pos pos, t_all *all)
{
	t_spr_lst	*tmp;
	t_spr_lst	*new;
	t_spr_lst	*last;

	last = NULL;
	new = ft_lstnew_sprite(all->player, pos, all, sprites);
	if (!*sprites)
		return ((*sprites = new));
	tmp = *sprites;
	while (tmp && new->distance < tmp->distance)
	{
		last = tmp;
		tmp = tmp->next;
	}
	if (!last)
	{
		new->next = tmp;
		*sprites = new;
	}
	else
	{
		new->next = last->next;
		last->next = new;
	}
	return (*sprites);
}

void		ft_sort_spites(t_spr_lst **sprites, char **map, t_all *all)
{
	int		x;
	int		y;
	t_pos	sprite_pos;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '2')
			{
				sprite_pos.x = (double)x + 0.5;
				sprite_pos.y = (double)y + 0.5;
				ft_sort_lst_sprites(sprites, sprite_pos, all);
			}
		}
	}
}
