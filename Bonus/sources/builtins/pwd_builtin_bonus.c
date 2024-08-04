/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:02:35 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

int	check_arguments(char **cmd)
{
	int	i;

	i = 1;
	while (cmd && cmd[i])
	{
		if (cmd[i][0] == '-')
		{
			ft_putstr_fd("minishell: pwd: ", STDERR_FILENO);
			ft_putstr_fd(cmd[i], STDERR_FILENO);
			ft_putstr_fd(": invalid option\n", STDERR_FILENO);
			g_exit.status = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

void	_pwd(t_env *env, char **cmd, int fd)
{
	t_env	*cwd;

	if (check_arguments(cmd) != 0)
		return ;
	cwd = get_env_node(env, "2PWD");
	ft_putstr_fd(cwd->value, fd);
	ft_putstr_fd("\n", fd);
	g_exit.status = 0;
}
