/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:08:00 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

int	parse_command(t_tree **root, t_token **tok)
{
	t_tree	*cmd;
	int		err;

	cmd = (t_tree *)ft_malloc(sizeof(t_tree));
	if (!cmd)
		return (-1);
	init_cmd_node(cmd);
	err = 0;
	while (err == 0 && *tok && (*tok)->type != PIPE && (*tok)->type != AND
		&& (*tok)->type != OR && (*tok)->type != L_PAREN
		&& (*tok)->type != R_PAREN)
	{
		if (is_redir_in((*tok)->type) || is_redir_out((*tok)->type))
			err = build_list(&cmd->cmd.redir, tok);
		else
			err = build_list(&cmd->cmd.list, tok);
		if (*tok && (*tok)->type == SPC)
			*tok = (*tok)->next;
	}
	*root = cmd;
	return (err);
}

int	parse_pipeline(t_tree **root, t_token **tokens)
{
	t_tree	*cmd;
	int		err;

	err = 0;
	cmd = NULL;
	skip(tokens, SPC);
	if (*tokens && (*tokens)->type != R_PAREN && (*tokens)->type != PIPE)
		err = parse_command(root, tokens);
	while (1)
	{
		if (peek(*tokens) == PIPE)
		{
			skip(tokens, PIPE);
			err = parse_command(&cmd, tokens);
			if (err < 0)
				return (err);
			*root = new_tree_node(T_PIPE, *root, cmd);
			if (!*root)
				return (-1);
		}
		else
			return (err);
	}
	return (err);
}

int	parse_condition(t_tree **root, t_token **tokens)
{
	t_tree		*pipeline;
	t_type		type;
	int			err;

	err = 0;
	pipeline = NULL;
	skip(tokens, SPC);
	if (*tokens && (*tokens)->type != OR && (*tokens)->type != AND)
		err = parse_pipeline(root, tokens);
	while (1)
	{
		if (peek(*tokens) == OR || peek(*tokens) == AND)
		{
			type = condition_node_type(tokens);
			err = parse_pipeline(&pipeline, tokens);
			if (err < 0)
				return (err);
			*root = new_tree_node(type, *root, pipeline);
			if (!*root)
				return (-1);
		}
		else
			return (err);
	}
	return (err);
}

int	parse_group(t_tree **root, t_token **tokens)
{
	t_tree	*group;
	int		err;

	err = 0;
	group = NULL;
	skip(tokens, L_PAREN);
	group = parser(tokens);
	if (!group)
		return (-1);
	else
		skip(tokens, R_PAREN);
	err = add_group_redir(*tokens, group);
	skip_redirs(tokens);
	if (peek(*tokens) == PIPE)
		err = parse_pipeline(&group, tokens);
	subshell_root_type(group);
	if (!*root)
		*root = group;
	else
		(*root)->node.rchild = group;
	return (err);
}

t_tree	*parser(t_token **tokens)
{
	t_tree	*root;
	int		err;

	err = 0;
	root = NULL;
	while (*tokens)
	{
		if (*tokens && (*tokens)->type == R_PAREN)
			break ;
		else if (*tokens && (*tokens)->type == L_PAREN)
			err = parse_group(&root, tokens);
		else if (peek(*tokens) == OR || peek(*tokens) == AND)
			err = parse_condition(&root, tokens);
		else
			err = parse_pipeline(&root, tokens);
		if (err != 0)
			return (NULL);
	}
	return (root);
}
