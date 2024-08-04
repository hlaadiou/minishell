/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:51:24 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 00:16:40 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_all(void)
{
	t_garb	*next;

	while (g_exit.gc)
	{
		next = (g_exit.gc)->next;
		free((g_exit.gc)->ptr);
		free(g_exit.gc);
		g_exit.gc = next;
	}
	g_exit.gc = NULL;
}

int	garbage_list_add(t_garb **gc, void *ptr)
{
	t_garb	*tmp;

	tmp = *gc;
	if (!*gc)
	{
		*gc = (t_garb *)malloc(sizeof(t_garb));
		tmp = *gc;
	}
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = (t_garb *)malloc(sizeof(t_garb));
		tmp = tmp->next;
	}
	if (!tmp)
		return (1);
	tmp->ptr = ptr;
	tmp->next = NULL;
	return (0);
}

void	*ft_malloc(size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
	{
		clean_all();
		ft_putstr_fd("unexpected malloc fail occured\n", STDERR_FILENO);
		g_exit.status = ALLOCERR;
	}
	else if (new && garbage_list_add(&g_exit.gc, new) != 0)
	{
		clean_all();
		ft_putstr_fd("unexpected malloc fail occured\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (new);
}
