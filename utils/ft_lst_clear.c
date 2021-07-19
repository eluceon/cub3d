/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 21:47:44 by eluceon           #+#    #+#             */
/*   Updated: 2021/01/05 22:54:48 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_lst_clear(t_list **lst)
{
	t_list	*tmp1;
	t_list	*tmp2;

	if (*lst)
	{
		tmp1 = *lst;
		while (tmp1)
		{
			tmp2 = tmp1->next;
			free(tmp1->content);
			free(tmp1);
			tmp1 = tmp2;
		}
		*lst = NULL;
	}
}
