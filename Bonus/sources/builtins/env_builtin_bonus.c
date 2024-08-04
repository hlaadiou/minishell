/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:45:14 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	_env(t_env *env, char **arg, int fd)
{
	if (arg[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", STDERR_FILENO);
		g_exit.status = 2;
		return ;
	}
	while (env)
	{
		if (env->name && env->value && !env->hide)
		{
			ft_putstr_fd(env->name, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(env->value, fd);
			ft_putstr_fd("\n", fd);
		}
		env = env->next;
	}
	g_exit.status = 0;
}
