/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredocs_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:08:25 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

t_token	*get_hdoc_delim(t_token **redir)
{
	t_token	*delim;
	char	*var;

	delim = NULL;
	while (1)
	{
		var = hdoc_expand(*redir);
		if (!var)
		{
			*redir = (*redir)->next;
			continue ;
		}
		if (token_list_add(&delim, (*redir)->type, var, ft_strlen(var)) != 0)
			return (NULL);
		*redir = (*redir)->next;
		if (!*redir \
			|| is_redir_in((*redir)->type) || is_redir_out((*redir)->type))
			break ;
	}
	if (delim)
		delim = redir_join(delim);
	return (delim);
}

int	update_hdoc_fd(t_tree *cmd, t_env *env)
{
	t_token	*redir;
	t_token	*delim;

	delim = NULL;
	if (cmd->type != T_CMD && cmd->type != S_CMD)
		return (0);
	redir = cmd->cmd.redir;
	while (redir)
	{
		if (redir->type == HDOC || redir->type == HDOC_EXP)
		{
			if (cmd->cmd.hdoc != -1)
				close(cmd->cmd.hdoc);
			delim = get_hdoc_delim(&redir);
			cmd->cmd.hdoc = open_heredoc(delim, env);
			if (cmd->cmd.hdoc == -1)
				return (1);
		}
		if (redir && redir->type != HDOC && redir->type != HDOC_EXP)
			redir = redir->next;
	}
	return (0);
}

int	get_hdoc_fd(t_tree *cmd, t_env *env)
{
	t_token	*redir;
	t_token	*delim;
	int		fd;

	delim = NULL;
	fd = -1;
	while (cmd && cmd->type != T_CMD && cmd->type != S_CMD)
		cmd = cmd->node.lchild;
	redir = cmd->cmd.sub_redir;
	while (redir)
	{
		if (redir->type == HDOC || redir->type == HDOC_EXP)
		{
			if (fd != -1)
				close(fd);
			delim = get_hdoc_delim(&redir);
			fd = open_heredoc(delim, env);
			if (fd == -1)
				return (-2);
		}
		if (redir && redir->type != HDOC && redir->type != HDOC_EXP)
			redir = redir->next;
	}
	return (fd);
}

int	open_subsh_hdoc(t_tree *root, t_env *env)
{
	int	sub_hdoc;

	if (update_hdoc_fd(root, env) == 1)
		return (1);
	sub_hdoc = get_hdoc_fd(root, env);
	if (sub_hdoc == -2)
		return (1);
	update_subshell_hdoc(root, sub_hdoc);
	return (0);
}

int	open_heredocs(t_tree *root, t_env *env)
{
	if (!root)
		return (1);
	if (root->type == T_CMD)
	{
		if (update_hdoc_fd(root, env) == 1)
			return (1);
	}
	else if (is_subshell(root->type))
	{
		if (open_subsh_hdoc(root, env) == 1)
			return (1);
	}
	else
	{
		if (open_heredocs(root->node.lchild, env) == 1)
			return (1);
		if (open_heredocs(root->node.rchild, env) == 1)
			return (1);
	}
	return (0);
}
