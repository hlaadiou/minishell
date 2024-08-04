/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:28:51 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:53:55 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd_home(t_env *env, char **home)
{
	*home = get_env_value(env, "HOME");
	if (!*home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		g_exit.status = 1;
		return (1);
	}
	return (0);
}

int	cd_old_pwd(t_env *env, char **old_pwd)
{
	*old_pwd = get_env_value(env, "OLDPWD");
	if (!*old_pwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		g_exit.status = 1;
		return (1);
	}
	return (0);
}

void	update_pwd(t_env **env, char *new_pwd)
{
	if (!get_env_value(*env, "PWD"))
		env_node_insert(env, ft_strdup("PWD"), new_pwd, 1);
	else
		update_env_value(env, ft_strdup("PWD"), new_pwd, 0);
	update_env_value(env, ft_strdup("2PWD"), ft_strdup(new_pwd), 0);
}

int	change_dir(t_env **env, char *dir, char **cmd, int fd)
{
	char	*cwd;

	if (chdir(dir) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(dir, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror(NULL);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd && (!ft_strcmp(cmd[1], "..") || !ft_strcmp(cmd[1], ".")))
	{
		if (!ft_strcmp(cmd[1], ".."))
			update_pwd(env, ft_strjoin(get_env_value(*env, "2PWD"), "/.."));
		else
			update_pwd(env, ft_strjoin(get_env_value(*env, "2PWD"), "/."));
		ft_putstr_fd("cd: error retrieving current directory: getcwd: \
cannot access parent directories: ", STDERR_FILENO);
		perror(NULL);
	}
	else if (cmd[1] && !ft_strcmp(cmd[1], "-"))
		_pwd(*env, NULL, fd);
	if (cwd)
		update_pwd(env, cwd);
	return (g_exit.status = 0, 0);
}

void	_cd(char **cmd, t_env *env, int fd)
{
	char	*dir;
	char	*pwd;

	if (!cmd[1])
	{
		if (cd_home(env, &dir) != 0)
			return ;
	}
	else if (!ft_strcmp(cmd[1], "-"))
	{
		if (cd_old_pwd(env, &dir) != 0)
			return ;
	}
	else
		dir = cmd[1];
	pwd = get_env_value(env, "PWD");
	if (pwd)
		pwd = ft_strdup(pwd);
	if (change_dir(&env, dir, cmd, fd) == 0)
		update_env_value(&env, ft_strdup("OLDPWD"), pwd, 0);
	else
	{
		g_exit.status = 1;
		free(pwd);
	}
}
