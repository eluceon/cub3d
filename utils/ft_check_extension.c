/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_extension.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:50:10 by eluceon           #+#    #+#             */
/*   Updated: 2021/01/28 15:09:50 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** The function ft_check_extension() checks file extension. It compares file
** check_file has extension ext.
** ft_check_extension() returns 1 if extensions are equal and 0 if extensions
** are not equal.
*/

int	ft_check_extension(char *check_file, char *ext)
{
	int	ext_len;
	int	file_len;

	if (!check_file || !ext)
		return (0);
	ext_len = 0;
	file_len = 0;
	while (ext[ext_len])
		ext_len++;
	while (check_file[file_len])
		file_len++;
	if (file_len <= ext_len)
		return (0);
	while (ext_len > 0)
	{
		if (check_file[--file_len] != ext[--ext_len])
			return (0);
	}
	return (1);
}
