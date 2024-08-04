/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp_utils3_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:08:00 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	update_redirs(t_tree *root, t_token *sub_redir)
{
	if (root->type == T_CMD || root->type == S_CMD)
		root->cmd.sub_redir = sub_redir;
	else
	{
		update_redirs(root->node.lchild, sub_redir);
		update_redirs(root->node.rchild, sub_redir);
	}
}

int	add_group_redir(t_token *paren, t_tree *group)
{
	t_token	*sub_redir;
	int		err;

	err = 0;
	sub_redir = NULL;
	if (!paren)
		return (err);
	skip(&paren, SPC);
	while (paren && paren->type != R_PAREN && paren->type != L_PAREN
		&& !is_connector(paren))
	{
		if (is_redir_out(paren->type) || is_redir_in(paren->type))
			err = build_list(&sub_redir, &paren);
		else if (paren->type == SPC)
			paren = paren->next;
		if (err != 0)
			return (err);
	}
	update_redirs(group, sub_redir);
	return (err);
}

void	skip_redirs(t_token **tok)
{
	while (*tok)
	{
		if (is_redir_in((*tok)->type) || is_redir_out((*tok)->type))
		{
			while (*tok && (*tok)->type != SPC && (*tok)->type != L_PAREN
				&& (*tok)->type != R_PAREN && (*tok)->type != AND
				&& (*tok)->type != OR && (*tok)->type != PIPE)
				*tok = (*tok)->next;
		}
		if (*tok && (*tok)->type == SPC)
			*tok = (*tok)->next;
		else
			break ;
	}
}
