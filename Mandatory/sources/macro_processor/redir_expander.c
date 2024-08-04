/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:31:10 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 02:44:26 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*wild_redirlst_exp(t_token *rdirlst, int **flags)
{
	t_token	*wild_rdirlst;
	int		pos;

	pos = 0;
	wild_rdirlst = NULL;
	if (!flags)
		return (NULL);
	while (rdirlst)
	{
		if (wild_redir_exp(&wild_rdirlst, rdirlst, flags, &pos) == 1)
		{
			if (g_exit.status == AMBGRDIR)
				ambiguous_redir(rdirlst->lexeme);
			return (NULL);
		}
		rdirlst = rdirlst->next;
	}
	return (wild_rdirlst);
}

char	*grep_value(t_token	*tkn, t_env *env)
{
	char	*var;

	var = tkn->lexeme;
	if (var && *var == '$')
	{
		if (*(var + 1))
		{
			var = get_splitted_redir_var(env, var);
			if (!var && g_exit.status == AMBGRDIR)
				return (NULL);
			if (!var && (tkn->type == RD_OUT_DQ || tkn->type == RD_IN_DQ \
				|| tkn->type == APPEND_DQ || tkn->type == D_QUOTE))
				var = "";
			else if (!var && \
					(is_redir_in(tkn->type) || is_redir_out(tkn->type)))
			{
				if (check_ambiguity(tkn, env))
					return (g_exit.status = AMBGRDIR, NULL);
				choose_type(tkn);
			}
		}
		else
			truncate_dollar(tkn, &var);
	}
	return (var);
}

int	redir_update(t_token **redirlst, t_token *lst, t_env *env)
{
	char		*var;

	while (lst && lst->lexeme)
	{
		var = lst->lexeme;
		if (expandable_redir(lst))
			var = grep_value(lst, env);
		else if (lst->type == HDOC || lst->type == HDOC_EXP \
				|| !expandable_tkn(lst))
			var = hdoc_expand(lst);
		if (!var && g_exit.status == AMBGRDIR)
			return (1);
		if (var && \
			token_list_add(redirlst, lst->type, var, ft_strlen(var)) != 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	expand_redir_vars(t_token **newredir, t_token *lst, t_env *env)
{
	t_token	*splitted;

	splitted = redirlst_split(lst);
	set_redir_exit_status(splitted);
	if (redir_update(newredir, splitted, env))
		return (1);
	return (0);
}

t_token	*redir_expand(t_token *redir, t_env *env)
{
	t_token	*newredir;
	int		*flagtab;
	int		**flagvec;

	newredir = NULL;
	flagvec = NULL;
	if (env)
	{
		if (expand_redir_vars(&newredir, redir, env) == 1)
			return (NULL);
		expand_rdir_tilde(newredir, env);
	}
	flagtab = create_wildflags(newredir);
	newredir = redir_join(newredir);
	if (flagtab)
	{
		flagvec = create_wildvec(flagtab, newredir);
		free(flagtab);
		newredir = wild_redirlst_exp(newredir, flagvec);
		clean_intvec(flagvec);
	}
	return (newredir);
}
