/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expander_utils4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 02:42:45 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 02:44:12 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*hdoc_expand(t_token *tkn)
{
	char	*var;

	var = tkn->lexeme;
	if ((tkn->type == HDOC_EXP || tkn->type == WORD) && tkn->next \
		&& (tkn->next->type == D_QUOTE || tkn->next->type == S_QUOTE))
	{
		if (var && *var == '$' && !*(var + 1))
		{
			if (tkn->type == HDOC_EXP)
				tkn->next->type = HDOC;
			else
				tkn->next->type = hdoc_pick_type(tkn->next);
			var = NULL;
		}
	}
	return (var);
}

int	expandable_rdir_tilde(t_token *lst)
{
	if (!lst)
		return (0);
	if ((lst->type == WORD || lst->type == RD_IN_WD || lst->type == RD_OUT_WD \
		|| lst->type == APPEND_WD) \
		&& *lst->lexeme == '~' \
		&& (!*(lst->lexeme + 1)) \
		&& (!lst->next || (lst->next && lst->next->type == SPC)) \
		&& (!lst->prev || (lst->prev && lst->prev->type == SPC)))
		return (1);
	else if ((lst->type == WORD || lst->type == RD_IN_WD \
			|| lst->type == RD_OUT_WD \
			|| lst->type == APPEND_WD) \
			&& *lst->lexeme == '~' \
			&& *(lst->lexeme + 1) && *(lst->lexeme + 1) == '/' \
			&& (!lst->prev || (lst->prev && lst->prev->type == SPC)))
		return (1);
	else
		return (0);
}

void	expand_rdir_tilde(t_token *lst, t_env *env)
{
	char	*home;
	char	*newlex;

	home = get_home(env);
	if (!home)
		return ;
	while (lst)
	{
		newlex = NULL;
		if (expandable_rdir_tilde(lst))
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

int	wild_redir_match(t_token **lst, t_entry *matches, char *dir, \
		t_node_type type)
{
	char	*wildlex;

	if ((is_redir_in(type) || is_redir_out(type)) && matches->next)
	{
		g_exit.status = AMBGRDIR;
		return (1);
	}
	while (matches)
	{
		if (dir)
			wildlex = ft_strjoin(dir, matches->name);
		else
			wildlex = matches->name;
		if (!wildlex || \
		token_list_add(lst, type, wildlex, ft_strlen(wildlex)) != 0)
			return (1);
		if (dir)
			free(wildlex);
		matches = matches->next;
	}
	return (0);
}

int	wild_redir_exp(t_token **newlst, t_token *tkn, int **flags, int *pos)
{
	t_entry	*matches;
	char	*pattern;
	char	*dir;

	dir = NULL;
	pattern = NULL;
	matches = NULL;
	if (ft_strchr(tkn->lexeme, '*') || ft_strchr(tkn->lexeme, '?'))
	{
		extract_dir_pattern(&dir, &pattern, tkn);
		matches = dir_pattern_check(dir, pattern, flags[(*pos)++]);
	}
	if (matches)
	{
		if (wild_redir_match(newlst, matches, dir, tkn->type) == 1)
			return (free(dir), free(pattern), clean_list(&matches), 1);
	}
	else
		if (token_list_add(newlst, tkn->type, tkn->lexeme, \
				ft_strlen(tkn->lexeme)) != 0)
			return (free(dir), free(pattern), 1);
	free(pattern);
	free(dir);
	clean_list(&matches);
	return (0);
}
