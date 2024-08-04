/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expander_utils1_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 02:37:42 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	set_redir_exit_status(t_token *redir)
{
	while (redir)
	{
		if (redir->type == RD_IN_WD || redir->type == RD_IN_DQ \
		|| redir->type == RD_OUT_WD || redir->type == RD_OUT_DQ \
		|| redir->type == APPEND_WD || redir->type == APPEND_DQ \
		|| (redir->type == WORD && expandable_tkn(redir)) \
		|| (redir->type == D_QUOTE && expandable_tkn(redir)))
		{
			if (redir->lexeme && !ft_strcmp(redir->lexeme, "$?"))
			{
				redir->lexeme = ft_itoa(g_exit.status);
				if (redir->lexeme)
					garbage_list_add(&g_exit.gc, redir->lexeme);
			}
		}
		redir = redir->next;
	}
}

int	expandable_redir(t_token *lst)
{
	if (lst->type == RD_IN_WD || lst->type == RD_OUT_WD \
	|| lst->type == APPEND_WD \
	|| (lst->type == WORD && expandable_tkn(lst)) \
	|| lst->type == RD_IN_DQ || lst->type == RD_OUT_DQ \
	|| lst->type == APPEND_DQ \
	|| (lst->type == D_QUOTE && expandable_tkn(lst)))
		return (1);
	return (0);
}

void	truncate_dollar(t_token *tkn, char **var)
{
	if ((tkn->type == WORD || tkn->type == RD_IN_WD || tkn->type == RD_OUT_WD \
			|| tkn->type == APPEND_WD) && tkn->next && \
			(tkn->next->type == D_QUOTE || tkn->next->type == S_QUOTE))
	{
		if (tkn->type == RD_IN_WD || tkn->type == RD_OUT_WD \
			|| tkn->type == APPEND_WD)
			choose_type(tkn);
		*var = NULL;
	}
}

char	*get_splitted_redir_var(t_env *env, char *var)
{
	char	**splitted;
	char	*value;
	int		len;

	len = 0;
	value = get_env_value(env, var + 1);
	splitted = ft_split(value, BLANK);
	while (splitted && splitted[len])
		len++;
	clean_vec(splitted);
	if (len > 1)
	{
		ambiguous_redir(var);
		g_exit.status = AMBGRDIR;
		return (NULL);
	}
	return (value);
}

int	check_ambiguity(t_token *tkn, t_env *env)
{
	t_token	*original;
	char	*error;
	char	*errtmp;

	original = tkn;
	error = ft_strdup(tkn->lexeme);
	tkn = tkn->next;
	while (tkn)
	{
		if (tkn->type == WORD && tkn->lexeme && *tkn->lexeme == '$' \
			&& *(tkn->lexeme + 1) && !get_env_value(env, tkn->lexeme + 1))
		{
			errtmp = error;
			error = ft_strjoin(errtmp, tkn->lexeme);
			free(errtmp);
			tkn = tkn->next;
		}
		else if (tkn->type != SPC \
			&& !is_redir_in(tkn->type) && !is_redir_out(tkn->type))
			return (free(error), 0);
		else
			break ;
	}
	ambiguous_redir(error);
	return (free(error), 1);
}
