/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:30:31 by eluceon           #+#    #+#             */
/*   Updated: 2021/02/11 18:03:36 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void			*ft_calloc(size_t count, size_t size);
void			ft_putendl_fd(char *s, int fd);
t_list			*ft_lstnew(void *content);
void			ft_lst_clear(t_list **lst);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_check_extension(char *check_file, char *ext);
int				ft_skip_spaces(char *str, int *i);
int				ft_iswhitespace(int c);
int				ft_atoi_cub(const char *str, int *i);
int				ft_error_message(int error);
int				ft_lstsize(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
int				ft_strlen(const char *s);
int				ft_isemtyline(char *line);

#endif
