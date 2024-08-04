/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils7.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:26:53 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 01:30:32 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	default_fds(int **fildes)
{
	(*fildes)[0] = STDIN_FILENO;
	(*fildes)[1] = STDOUT_FILENO;
}

size_t	tkn_lst_size(t_token *lst)
{
	size_t	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

size_t	count_words(t_token *list)
{
	size_t	words;

	words = 0;
	while (list)
	{
		if (list->type == WORD)
			words++;
		list = list->next;
	}
	return (words);
}

size_t	lst_size(t_env *env)
{
	size_t	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

size_t	env_size(t_env *env)
{
	size_t	size;

	size = 0;
	while (env)
	{
		if (env->value && !env->hide)
			size++;
		env = env->next;
	}
	return (size);
}
