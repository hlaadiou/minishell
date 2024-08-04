/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 13:44:32 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 03:10:24 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_pattern(char *str, char *pattern, t_data *data)
{
	while (str[data->i])
	{
		if (pattern[data->j] && (pattern[data->j] == str[data->i]
				|| (pattern[data->j] == '?' && data->flags[data->flags_i++])))
		{
			data->i++;
			data->j++;
		}
		else if (pattern[data->j] && pattern[data->j] == '*'
			&& data->flags[data->flags_i++])
		{
			data->pat_i = data->j;
			data->str_i = data->i;
			data->j++;
		}
		else if (data->pat_i != -1)
		{
			data->i = ++data->str_i;
			data->j = data->pat_i + 1;
			data->flags_i--;
		}
		else
			return (0);
	}
	return (1);
}

int	wildcard_match(char *str, char *pattern, int *flags)
{
	t_data	data;

	data.j = 0;
	data.i = 0;
	data.str_i = -1;
	data.pat_i = -1;
	data.flags = flags;
	data.flags_i = 0;
	if (!str || !str[0])
		return (0);
	if (!check_pattern(str, pattern, &data))
		return (0);
	if (str[0] == '.' && pattern[0] != '.')
		return (0);
	while (pattern[data.j] && pattern[data.j] == '*')
		data.j++;
	if (!pattern[data.j])
		return (1);
	return (0);
}
