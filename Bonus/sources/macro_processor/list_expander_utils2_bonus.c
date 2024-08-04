/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_expander_utils2_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 02:24:43 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

t_token	*tkn_join(t_token *lst)
{
	t_token		*joined;
	char		*newlex;
	char		*tmp;

	joined = NULL;
	while (lst)
	{
		newlex = NULL;
		while (lst && lst->type != SPC)
		{
			tmp = newlex;
			newlex = ft_strjoin(tmp, lst->lexeme);
			free(tmp);
			lst = lst->next;
		}
		if (newlex)
			if (token_list_add(&joined, WORD, newlex, ft_strlen(newlex)) != 0)
				return (free(newlex), NULL);
		if (lst)
			lst = lst->next;
		free(newlex);
	}
	return (joined);
}

int	get_splitted_lst_var(t_token **lst, t_token *tkn, t_env *env)
{
	t_token	*splitted;
	t_token	*last;
	char	**vars;
	int		i;

	i = 0;
	splitted = NULL;
	last = NULL;
	vars = ft_split(get_env_value(env, tkn->lexeme + 1), BLANK);
	while (vars && vars[i])
	{
		if (token_list_add(&splitted, tkn->type, vars[i], \
			ft_strlen(vars[i])) != 0)
			return (1);
		if (vars[i + 1] && token_list_add(&splitted, SPC, " ", 1) != 0)
			return (1);
		i++;
	}
	clean_vec(vars);
	last = lst_last(*lst);
	if (!last)
		*lst = splitted;
	else
		last->next = splitted;
	return (0);
}

void	set_lst_exit_status(t_token *sub)
{
	while (sub)
	{
		if (sub->type == WORD || sub->type == D_QUOTE)
		{
			if (sub->lexeme && !ft_strcmp(sub->lexeme, "$?"))
			{
				sub->lexeme = ft_itoa(g_exit.status);
				if (sub->lexeme)
					garbage_list_add(&g_exit.gc, sub->lexeme);
			}
		}
		sub = sub->next;
	}
}

int	subtkn_update(t_token **newlst, t_token *tkn, t_token *sub, t_env *env)
{
	char	*var;

	while (sub && sub->lexeme)
	{
		var = sub->lexeme;
		if (*var == '$' && *(var + 1) && tkn->type == D_QUOTE \
			&& !get_env_value(env, var + 1))
			var = "";
		else if (*var == '$' && *(var + 1))
		{
			if (get_splitted_lst_var(newlst, sub, env))
				return (1);
			var = NULL;
		}
		else if (*var == '$' && tkn->next \
		&& (tkn->next->type == D_QUOTE || tkn->next->type == S_QUOTE))
			var = NULL;
		if (var)
			if (token_list_add(newlst, sub->type, var, ft_strlen(var)) != 0)
				return (1);
		sub = sub->next;
	}
	return (0);
}

// Update the token if it is of type WORD or D_QUOTE
// into a new expanded token added to the 'newtknlst'.
int	tkn_update(t_token **newlst, t_token *lst, t_env *env)
{
	t_token	*sub;

	sub = tkn_split(lst);
	if (!sub)
	{
		if (g_exit.status == ALLOCERR)
			return (1);
		return (0);
	}
	set_lst_exit_status(sub);
	if (subtkn_update(newlst, lst, sub, env) != 0)
		return (1);
	return (0);
}
