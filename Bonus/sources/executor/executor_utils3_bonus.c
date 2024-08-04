/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:36:24 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	_wait(pid_t pid)
{
	ignore_signals();
	waitpid(pid, &g_exit.status, 0);
	signal_interrupter();
	if (WIFEXITED(g_exit.status))
		g_exit.status = WEXITSTATUS(g_exit.status);
	else if (WIFSIGNALED(g_exit.status))
		g_exit.status = 128 + WTERMSIG(g_exit.status);
}

pid_t	_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		_error("fork failed");
	return (pid);
}

void	execute_builtin(char **cmd, t_env **env, int *files)
{
	if (!ft_strcmp(cmd[0], "cd"))
		_cd(cmd, *env, files[1]);
	else if (!ft_strcmp(cmd[0], "echo"))
		_echo(cmd, files[1]);
	else if (!ft_strcmp(cmd[0], "pwd"))
		_pwd(*env, cmd, files[1]);
	else if (!ft_strcmp(cmd[0], "export"))
		_export(cmd, env, files[1]);
	else if (!ft_strcmp(cmd[0], "unset"))
		_unset(env, cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		_env(*env, cmd, files[1]);
	else if (!ft_strcmp(cmd[0], "exit"))
		_exit_(env, cmd);
}

void	exec_builtins(t_tree *node, t_env **env)
{
	int		*files;
	char	**cmd_vec;

	files = open_files(node->cmd);
	if (!files)
		return ;
	cmd_vec = build_builtin_vec(node->cmd.list);
	if (cmd_vec && cmd_vec[0])
		execute_builtin(cmd_vec, env, files);
	if (files[0] != STDIN_FILENO)
		close(files[0]);
	if (files[1] != STDOUT_FILENO)
		close(files[1]);
	free(files);
	clean_vec(cmd_vec);
}

int	check_for_builtins(t_tree *node, t_env **env)
{
	if (!is_builtin(node->cmd.list))
		return (0);
	exec_builtins(node, env);
	return (1);
}
