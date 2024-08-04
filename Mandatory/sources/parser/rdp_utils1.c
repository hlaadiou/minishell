/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:08:00 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 00:51:50 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node_type	peek(t_token *tokens)
{
	while (tokens && tokens->type != PIPE && tokens->type != AND
		&& tokens->type != OR && tokens->type != L_PAREN
		&& tokens->type != R_PAREN)
		tokens = tokens->next;
	if (!tokens)
		return (END);
	return (tokens->type);
}

void	skip(t_token **tokens, t_node_type type)
{
	while (*tokens && ((*tokens)->type == type || (*tokens)->type == SPC))
	{
		if ((*tokens)->type == type)
		{
			*tokens = (*tokens)->next;
			break ;
		}
		*tokens = (*tokens)->next;
	}
}

t_tree	*new_tree_node(t_type type, t_tree *left, t_tree *right)
{
	t_tree	*new;

	new = (t_tree *)ft_malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->type = type;
	new->node.lchild = left;
	new->node.rchild = right;
	new->cmd.list = NULL;
	new->cmd.redir = NULL;
	new->cmd.sub_redir = NULL;
	return (new);
}

t_type	condition_node_type(t_token **tokens)
{
	t_node_type	type;

	type = peek(*tokens);
	skip(tokens, type);
	if (type == PIPE)
		return (T_PIPE);
	else if (type == OR)
		return (T_OR);
	else if (type == AND)
		return (T_AND);
	else
		return (T_CMD);
}

void	subshell_root_type(t_tree *subsh)
{
	if (subsh->type == T_PIPE)
		subsh->type = S_PIPE;
	else if (subsh->type == T_OR)
		subsh->type = S_OR;
	else if (subsh->type == T_AND)
		subsh->type = S_AND;
	else if (subsh->type == T_CMD)
		subsh->type = S_CMD;
}
