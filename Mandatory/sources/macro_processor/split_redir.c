/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:45:28 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 02:34:36 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	assign_subredir_type(t_node_type *type, int ind)
{
	if (ind != 0 && (is_redir_in(*type) || is_redir_out(*type)))
	{
		if (*type == RD_IN_DQ || *type == RD_OUT_DQ \
		|| *type == APPEND_DQ || *type == HDOC)
			*type = D_QUOTE;
		else if (*type == RD_IN_WD || *type == RD_OUT_WD \
		|| *type == APPEND_WD || *type == HDOC_EXP)
			*type = WORD;
	}
	return ;
}

int	get_subredir(t_token **lst, t_token *redir, int size, int i)
{
	char		*sub;
	t_node_type	type;

	type = redir->type;
	sub = ft_substr(redir->lexeme, i, size);
	if (!sub)
	{
		g_exit.status = ALLOCERR;
		return (-1);
	}
	assign_subredir_type(&type, i);
	if (token_list_add(lst, type, sub, size) != 0)
	{
		free(sub);
		return (-1);
	}
	free(sub);
	return (size - 1);
}

//Subtokens of : 1-|<$"$""$USER$PATH"$NO'world'| 
//and            2-|<<$$$"$_"hi|
//are :          1-|$|->|"$USER"|->|"$PATH"|->|$NO|->|world|
//and            2-|$$|->|$|->|$_|->|hi|.
t_token	*redirtkn_split(t_token *redir)
{
	t_token	*subredir;
	int		size;
	int		i;
	int		j;

	i = -1;
	j = 0;
	subredir = NULL;
	if (redir->lexeme && !redir->lexeme[0] \
		&& token_list_add(&subredir, redir->type, redir->lexeme, 0) != 0)
		return (g_exit.status = ALLOCERR, NULL);
	while (redir->lexeme && redir->lexeme[++i])
	{
		if (redir->lexeme[i] == '$')
			size = get_subredir(&subredir, redir, \
					get_idsize(redir->lexeme, i), i);
		else
			size = get_subredir(&subredir, redir, \
					get_wordsize(redir->lexeme, i), i);
		if (size == -1)
			return (NULL);
		i += size;
	}
	return (subredir);
}

t_token	*redirlst_split(t_token *redir)
{
	t_token	*splitted;
	t_token	*tmp;

	splitted = NULL;
	while (redir)
	{
		tmp = NULL;
		if (redir->type != S_QUOTE && redir->type != RD_IN_SQ \
			&& redir->type != RD_OUT_SQ && redir->type != APPEND_SQ)
			tmp = redirtkn_split(redir);
		else if (token_list_add(&tmp, redir->type, redir->lexeme, \
				ft_strlen(redir->lexeme)) != 0)
			return (NULL);
		if (tmp == NULL && g_exit.status == ALLOCERR)
			return (NULL);
		while (tmp && tmp->lexeme)
		{
			if (token_list_add(&splitted, tmp->type, tmp->lexeme, \
						ft_strlen(tmp->lexeme)) != 0)
				return (NULL);
			tmp = tmp->next;
		}
		redir = redir->next;
	}
	return (splitted);
}
