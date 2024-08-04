/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 08:13:22 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 02:27:38 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	expandable_lst_tilde(t_token *lst)
{
	if (!lst)
		return (0);
	if ((lst->type == WORD && *lst->lexeme == '~' \
		&& (!*(lst->lexeme + 1))) \
		&& (!lst->next || (lst->next && lst->next->type == SPC)) \
		&& (!lst->prev || (lst->prev && lst->prev->type == SPC)))
		return (1);
	else if (lst->type == WORD && *lst->lexeme == '~' \
			&& *(lst->lexeme + 1) && *(lst->lexeme + 1) == '/' \
			&& (!lst->prev || (lst->prev && lst->prev->type == SPC)))
		return (1);
	else
		return (0);
}

void	expand_lst_tilde(t_token *lst, t_env *env)
{
	char	*home;
	char	*newlex;

	home = get_home(env);
	if (!home)
		return ;
	while (lst)
	{
		newlex = NULL;
		if (expandable_lst_tilde(lst))
		{
			if (!*(lst->lexeme + 1))
				newlex = ft_strdup(home);
			else if (*(lst->lexeme + 1) && *(lst->lexeme + 1) == '/')
				newlex = ft_strjoin(home, lst->lexeme + 1);
			if (newlex)
			{
				lst->lexeme = newlex;
				garbage_list_add(&g_exit.gc, newlex);
			}
		}
		lst = lst->next;
	}
	free(home);
}

int	expand_env_vars(t_token **newlst, t_token *lst, t_env *env)
{
	while (lst)
	{
		if (lst->lexeme \
		&& (lst->type == WORD || (lst->type == D_QUOTE && *lst->lexeme)))
		{
			if (tkn_update(newlst, lst, env) == 1)
				return (1);
		}
		else
			if (token_list_add(newlst, lst->type, lst->lexeme, \
					ft_strlen(lst->lexeme)) != 0)
				return (1);
		lst = lst->next;
	}
	return (0);
}

t_token	*list_expand(t_token *tokens, t_env *env)
{
	t_token	*newtknlst;
	int		*flagtab;
	int		**flagvec;

	newtknlst = NULL;
	flagvec = NULL;
	if (env)
	{
		if (expand_env_vars(&newtknlst, tokens, env) == 1)
			return (NULL);
		expand_lst_tilde(newtknlst, env);
	}
	flagtab = create_wildflags(newtknlst);
	newtknlst = tkn_join(newtknlst);
	if (flagtab)
	{
		flagvec = create_wildvec(flagtab, newtknlst);
		free(flagtab);
		newtknlst = wildlst_expand(newtknlst, flagvec);
		clean_intvec(flagvec);
	}
	return (newtknlst);
}

int	node_expand(t_cmd *cmd_node, t_env *env)
{
	if (!cmd_node)
		return (1);
	if (cmd_node->list)
	{
		cmd_node->list = list_expand(cmd_node->list, env);
		if (!cmd_node->list && g_exit.status == ALLOCERR)
			return (g_exit.status = 1, ALLOCERR);
	}
	if (cmd_node->redir)
	{
		cmd_node->redir = redir_expand(cmd_node->redir, env);
		if (!cmd_node->redir && g_exit.status == ALLOCERR)
			return (g_exit.status = 1, ALLOCERR);
		else if (!cmd_node->redir && g_exit.status == AMBGRDIR)
			return (g_exit.status = 1, AMBGRDIR);
	}
	if (cmd_node->sub_redir)
	{
		cmd_node->sub_redir = redir_expand(cmd_node->sub_redir, env);
		if (!cmd_node->sub_redir && g_exit.status == ALLOCERR)
			return (g_exit.status = 1, ALLOCERR);
		else if (!cmd_node->sub_redir && g_exit.status == AMBGRDIR)
			return (g_exit.status = 1, AMBGRDIR);
	}
	return (0);
}
