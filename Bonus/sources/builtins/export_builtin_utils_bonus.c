/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:54:02 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	print_env(t_env *env, int fd)
{
	while (env)
	{
		if (!env->hide)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(env->name, fd);
			if (env->value)
			{
				ft_putstr_fd("=\"", fd);
				ft_putstr_fd(env->value, fd);
				ft_putstr_fd("\"", fd);
			}
			ft_putstr_fd("\n", fd);
		}
		env = env->next;
	}
}

int	check_name(char *arg, int *append)
{
	int	i;
	int	size;

	i = 1;
	size = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			*append = 1;
		else if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (-1);
		if (arg[i] != '+')
			size++;
		i++;
	}
	return (size);
}
