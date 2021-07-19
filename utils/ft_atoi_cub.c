/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:42:41 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/11 17:26:35 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_atoi_cub(const char *str, int *i)
{
	int				sign;
	unsigned int	result;

	result = 0;
	sign = 1;
	while (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n' ||
			str[*i] == '\v' || str[*i] == '\f' || str[*i] == '\r')
		(*i)++;
	if (str[*i] == '-')
		sign = -1;
	if (str[*i] == '-')
		(*i)++;
	if (str[*i] < '0' || str[*i] > '9')
		return (-1);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		if (result < 214748364)
			result = result * 10 + str[(*i)] - '0';
		(*i)++;
	}
	return ((int)(result * sign));
}
