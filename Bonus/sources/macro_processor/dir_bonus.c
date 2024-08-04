/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:17:44 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 17:53:36 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	clean_list(t_entry **list)
{
	t_entry	*next;

	while (*list)
	{
		next = (*list)->next;
		free((*list)->name);
		free(*list);
		*list = next;
	}
}

t_entry	*dir_pattern_check(char *dir, char *pattern, int *flags)
{
	t_entry			*entries;
	DIR				*dirp;
	struct dirent	*info;

	if (!pattern)
		return (NULL);
	if (!dir)
		dirp = opendir(".");
	else
		dirp = opendir(dir);
	entries = NULL;
	if (!dirp)
		return (NULL);
	while (1)
	{
		info = readdir(dirp);
		if (info == NULL)
			break ;
		if (wildcard_match(info->d_name, pattern, flags))
			if (entry_node_insert(&entries, info->d_name) != 0)
				return (closedir(dirp), clean_list(&entries), NULL);
	}
	closedir(dirp);
	return (entries);
}
