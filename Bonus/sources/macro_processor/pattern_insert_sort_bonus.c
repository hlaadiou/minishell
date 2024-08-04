/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_insert_sort_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:27:52 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

t_entry	*new_entry_node(char *name)
{
	t_entry	*node;

	node = (t_entry *)malloc(sizeof(t_entry));
	if (!node)
		return (NULL);
	node->name = ft_strdup(name);
	if (!node->name)
		return (NULL);
	node->next = NULL;
	return (node);
}

void	entry_insert(t_entry **entries, t_entry *node, char *name)
{
	t_entry	*curr;
	t_entry	*next;

	curr = *entries;
	next = NULL;
	while (curr)
	{
		next = curr->next;
		if (next && ft_strcmp(next->name, name) > 0)
			break ;
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	if (!*entries)
		*entries = node;
	else if (*entries && !next)
		curr->next = node;
	else
	{
		curr->next = node;
		node->next = next;
	}
}

int	entry_node_insert(t_entry **list, char *name)
{
	t_entry	*node;

	node = new_entry_node(name);
	if (!node)
		return (1);
	if (*list && ft_strcmp((*list)->name, name) > 0)
	{
		node->next = *list;
		*list = node;
		return (0);
	}
	entry_insert(list, node, name);
	return (0);
}
