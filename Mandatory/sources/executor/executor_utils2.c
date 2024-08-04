/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:40:27 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 15:23:17 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_fildes(int *files)
{
	if (!files)
		exit(EXIT_FAILURE);
	if (files[0] != STDIN_FILENO)
	{
		dup2(files[0], STDIN_FILENO);
		close(files[0]);
	}
	if (files[1] != STDOUT_FILENO)
	{
		dup2(files[1], STDOUT_FILENO);
		close(files[1]);
	}
	free(files);
}

int	extract_status(void)
{
	if (WIFEXITED(g_exit.status))
		return (WEXITSTATUS(g_exit.status));
	else if (WIFSIGNALED(g_exit.status))
		return (128 + WTERMSIG(g_exit.status));
	return (0);
}

void	close_heredocs(t_tree *root)
{
	if (!root)
		return ;
	if (root->type == T_CMD || root->type == S_CMD)
	{
		if (root->cmd.hdoc != -1)
			close(root->cmd.hdoc);
		if (root->cmd.sub_hdoc != -1)
			close(root->cmd.sub_hdoc);
	}
	close_heredocs(root->node.lchild);
	close_heredocs(root->node.rchild);
}

int	exec_left_pipe(t_tree *node, t_env **env, int *fds, int *pid)
{
	pid[0] = _fork();
	if (pid[0] == -1)
		return (1);
	if (pid[0] == 0)
	{
		default_signals();
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		executor(node->node.lchild, env);
		exit(g_exit.status);
	}
	return (0);
}

int	exec_right_pipe(t_tree *node, t_env **env, int *fds, int *pid)
{
	pid[1] = _fork();
	if (pid[1] == -1)
		return (1);
	if (pid[1] == 0)
	{
		default_signals();
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		executor(node->node.rchild, env);
		exit(g_exit.status);
	}
	return (0);
}
