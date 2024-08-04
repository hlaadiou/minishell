/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:08:00 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 00:51:50 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redir_in(t_node_type type)
{
	if (type == RD_IN_WD || type == RD_IN_DQ || type == RD_IN_SQ
		|| type == HDOC || type == HDOC_EXP)
		return (1);
	return (0);
}

int	is_redir_out(t_node_type type)
{
	if (type == RD_OUT_WD || type == RD_OUT_SQ || type == RD_OUT_DQ
		|| type == APPEND_WD || type == APPEND_SQ || type == APPEND_DQ)
		return (1);
	return (0);
}

int	in_list(t_token *tok)
{
	if (!is_redir_in((tok)->type) && !is_redir_out((tok)->type)
		&& !is_connector(tok) && tok->type != L_PAREN
		&& tok->type != R_PAREN && tok->type != SPC)
		return (1);
	return (0);
}

int	build_list(t_token **ptr, t_token **tokens)
{
	int	len;

	len = ft_strlen((*tokens)->lexeme);
	if (token_list_add(ptr, (*tokens)->type, (*tokens)->lexeme, len) != 0)
		return (-1);
	*tokens = (*tokens)->next;
	while (*tokens && in_list(*tokens)) 
	{
		len = ft_strlen((*tokens)->lexeme);
		if (token_list_add(ptr, (*tokens)->type, (*tokens)->lexeme, len) != 0)
			return (-1);
		*tokens = (*tokens)->next;
	}
	if (*tokens && (*tokens)->type == SPC)
		if (token_list_add(ptr, SPC, " ", 1) != 0)
			return (-1);
	return (0);
}

void	init_cmd_node(t_tree *cmd)
{
	cmd->type = T_CMD;
	cmd->cmd.hdoc = -1;
	cmd->cmd.sub_hdoc = -1;
	cmd->cmd.list = NULL;
	cmd->cmd.redir = NULL;
	cmd->cmd.sub_redir = NULL;
	cmd->node.rchild = NULL;
	cmd->node.lchild = NULL;
}
