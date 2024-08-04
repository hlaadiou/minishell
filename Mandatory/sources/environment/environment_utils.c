/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 08:47:46 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 00:14:15 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*get_env_node(t_env *env, char *name)
{
	while (env)
	{
		if (env->name && !ft_strcmp(env->name, name))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*update_shell_lvl(void)
{
	char	*old_lvl;
	int		new_lvl;

	old_lvl = getenv("SHLVL");
	if (!old_lvl)
		return (ft_itoa(1));
	new_lvl = ft_atoi(old_lvl) + 1;
	return (ft_itoa(new_lvl));
}

char	*get_env_value(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(name, env->name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
