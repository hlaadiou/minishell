/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_insert_sort_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:27:52 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

t_env	*new_env_node(char *name, char *value, int hide)
{
	t_env	*var;

	var = (t_env *)malloc(sizeof(t_env));
	if (!var)
		return (NULL);
	var->name = name;
	var->value = value;
	var->hide = hide;
	var->next = NULL;
	return (var);
}

void	env_insert(t_env **env, t_env *node, char *name)
{
	t_env	*curr;
	t_env	*next;

	curr = *env;
	next = NULL;
	while (curr)
	{
		next = curr->next;
		if (next && !next->hide && ft_strcmp(next->name, name) > 0)
			break ;
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	if (!*env)
		*env = node;
	else if (*env && !next)
		curr->next = node;
	else
	{
		curr->next = node;
		node->next = next;
	}
}

int	env_node_insert(t_env **env, char *name, char *val, int hide)
{
	t_env	*node;

	node = new_env_node(name, val, hide);
	if (!node)
		return (1);
	if (*env && ft_strcmp((*env)->name, name) > 0)
	{
		node->next = *env;
		*env = node;
		return (0);
	}
	env_insert(env, node, name);
	return (0);
}
