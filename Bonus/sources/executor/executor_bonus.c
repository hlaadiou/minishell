/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:04:39 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 15:24:42 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

int	exec_cmd(t_tree *node, t_env **env)
{
	int	ret_exp;

	if (!node)
		return (1);
	ret_exp = node_expand(&node->cmd, *env);
	if (ret_exp == ALLOCERR)
		return (ALLOCERR);
	else if (ret_exp == 0)
		if (execute_command(node, env) != 0)
			return (1);
	return (0);
}

//fd[0] read end, fd[1] write end
int	exec_pipe(t_tree *node, t_env **env)
{
	int	fds[2];
	int	pid[2];
	int	stat;

	if (pipe(fds) == -1)
		return (_error("pipe failed"), 1);
	if (exec_left_pipe(node, env, fds, pid))
		return (1);
	if (exec_right_pipe(node, env, fds, pid))
		return (1);
	close(fds[0]);
	close(fds[1]);
	ignore_signals();
	if (wait(&stat) == pid[1])
		g_exit.status = stat;
	if (wait(&stat) == pid[1])
		g_exit.status = stat;
	close_heredocs(node);
	g_exit.status = extract_status();
	signal_interrupter();
	return (0);
}

int	exec_or(t_tree *node, t_env **env)
{
	int	ret;

	ret = executor(node->node.lchild, env);
	if (ret != 0)
		return (ret);
	if (g_exit.status != 0)
	{
		ret = executor(node->node.rchild, env);
		if (ret != 0)
			return (ret);
	}
	else
		close_heredocs(node);
	return (0);
}

int	exec_and(t_tree *node, t_env **env)
{
	int	ret;

	ret = executor(node->node.lchild, env);
	if (ret != 0)
		return (ret);
	if (g_exit.status == 0)
	{
		ret = executor(node->node.rchild, env);
		if (ret != 0)
			return (ret);
	}
	else
		close_heredocs(node);
	return (0);
}

int	executor(t_tree *root, t_env **env)
{
	int	err;

	err = 0;
	if (!root)
		return (1);
	if (is_subshell(root->type))
		subshell(root, env);
	else if (root->type == T_OR)
		err = exec_or(root, env);
	else if (root->type == T_AND)
		err = exec_and(root, env);
	else if (root->type == T_PIPE)
		err = exec_pipe(root, env);
	else
		err = exec_cmd(root, env);
	if (err != 0)
		return (err);
	return (0);
}
