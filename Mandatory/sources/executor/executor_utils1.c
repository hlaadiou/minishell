/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:42:39 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 01:43:22 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_child(t_tree *node, t_env *env)
{
	int		*files;
	char	**cmd_vec;
	char	**env_vec;

	default_signals();
	files = open_files(node->cmd);
	set_fildes(files);
	if (!node->cmd.list)
		exit(0);
	cmd_vec = build_vec(node->cmd.list, env);
	env_vec = build_env_vec(env);
	execve(cmd_vec[0], cmd_vec, env_vec);
	cmd_not_found(node->cmd.list->lexeme);
	exit(EXIT_FAILURE);
}

int	execute_command(t_tree *node, t_env **env)
{
	pid_t	pid;

	if (check_for_builtins(node, env))
		return (0);
	pid = fork();
	if (pid == -1)
	{
		_error("fork failure");
		return (1);
	}
	if (pid == 0)
		execute_child(node, *env);
	else
	{
		ignore_signals();
		_wait(pid);
		if (node->cmd.hdoc != -1)
			close(node->cmd.hdoc);
	}
	return (0);
}
