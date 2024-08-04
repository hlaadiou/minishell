/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils9_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:22:34 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

int	*open_subsh_files(t_cmd subsh)
{
	t_token	*redir;
	t_token	*tmpredir;
	int		*fildes;

	fildes = (int *)malloc(2 * sizeof(int));
	if (!fildes)
		return (NULL);
	redir = subsh.sub_redir;
	tmpredir = NULL;
	default_fds(&fildes);
	if (subsh.sub_hdoc != -1)
		fildes[0] = subsh.sub_hdoc;
	while (redir)
	{
		if (open_append_files(redir, &fildes))
			return (NULL);
		else if (open_out_files(redir, &fildes))
			return (NULL);
		else if (open_in_files(redir, &tmpredir))
			return (NULL);
		redir = redir->next;
	}
	if (hdoc_or_rd_in(subsh.redir, tmpredir, &fildes))
		return (NULL);
	return (fildes);
}

int	is_subshell(t_type type)
{
	if (type == S_PIPE \
		|| type == S_OR \
		|| type == S_AND \
		|| type == S_CMD)
		return (1);
	return (0);
}

void	set_subshell_files(t_tree *subsh)
{
	int	*files;

	while (subsh && subsh->type != S_CMD && subsh->type != T_CMD)
		subsh = subsh->node.lchild;
	files = open_subsh_files(subsh->cmd);
	set_fildes(files);
}

void	subshell(t_tree *subsh, t_env **env)
{
	pid_t	pid;

	pid = _fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		set_subshell_files(subsh);
		if (subsh->type == S_OR)
			subsh->type = T_OR;
		else if (subsh->type == S_AND)
			subsh->type = T_AND;
		else if (subsh->type == S_PIPE)
			subsh->type = T_PIPE;
		else if (subsh->type == S_CMD)
			subsh->type = T_CMD;
		executor(subsh, env);
		clean_all();
		exit(g_exit.status);
	}
	else
	{
		close_heredocs(subsh);
		_wait(pid);
	}
}
