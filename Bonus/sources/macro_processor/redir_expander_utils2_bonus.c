/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expander_utils2_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 02:40:21 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	assign_rd_in(t_token *tkn)
{
	if (tkn->next && tkn->next->type == WORD)
		tkn->next->type = RD_IN_WD;
	else if (tkn->next && tkn->next->type == D_QUOTE)
		tkn->next->type = RD_IN_DQ;
	else if (tkn->next && tkn->next->type == S_QUOTE)
		tkn->next->type = RD_IN_SQ;
}

void	assign_rd_out(t_token *tkn)
{
	if (tkn->next && tkn->next->type == WORD)
		tkn->next->type = RD_OUT_WD;
	else if (tkn->next && tkn->next->type == D_QUOTE)
		tkn->next->type = RD_OUT_DQ;
	else if (tkn->next && tkn->next->type == S_QUOTE)
		tkn->next->type = RD_OUT_SQ;
}

void	assign_append(t_token *tkn)
{
	if (tkn->next && tkn->next->type == WORD)
		tkn->next->type = APPEND_WD;
	else if (tkn->next && tkn->next->type == D_QUOTE)
		tkn->next->type = APPEND_DQ;
	else if (tkn->next && tkn->next->type == S_QUOTE)
		tkn->next->type = APPEND_SQ;
}

void	choose_type(t_token *tkn)
{
	if (tkn && (tkn->type == RD_IN_WD || tkn->type == RD_IN_DQ \
		|| tkn->type == RD_IN_SQ))
		assign_rd_in(tkn);
	else if (tkn && (tkn->type == RD_OUT_WD || tkn->type == RD_OUT_DQ \
		|| tkn->type == RD_OUT_SQ))
		assign_rd_out(tkn);
	else if (tkn && (tkn->type == APPEND_WD || tkn->type == APPEND_DQ \
		|| tkn->type == APPEND_SQ))
		assign_append(tkn);
}

t_node_type	hdoc_pick_type(t_token *lst)
{
	t_node_type	inherited;

	inherited = lst->type;
	if (lst && inherited == HDOC_EXP)
	{
		lst = lst->next;
		while (lst && lst->type != SPC && !is_redir_in(lst->type) \
				&& !is_redir_out(lst->type))
		{
			if (lst->type == D_QUOTE || lst->type == S_QUOTE)
				return (HDOC);
			lst = lst->next;
		}
	}
	return (inherited);
}
