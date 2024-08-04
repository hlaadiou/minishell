/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expander_utils3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 02:41:47 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 02:42:41 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ambiguous_redir(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
	return ;
}

void	join_filename(t_token **redir, char **newfile)
{
	char	*tmp;
	int		toggle;

	toggle = 1;
	while (toggle \
			|| (*redir && (*redir)->type != SPC && !is_redir_in((*redir)->type) \
			&& !is_redir_out((*redir)->type)))
	{
		toggle = 0;
		tmp = *newfile;
		*newfile = ft_strjoin(tmp, (*redir)->lexeme);
		free(tmp);
		(*redir) = (*redir)->next;
	}
}

t_token	*redir_join(t_token *redir)
{
	t_node_type	inherited;
	t_token		*joined;
	char		*newfile;

	joined = NULL;
	while (redir)
	{
		newfile = NULL;
		inherited = hdoc_pick_type(redir);
		join_filename(&redir, &newfile);
		if (newfile)
		{
			if (token_list_add(&joined, inherited, newfile, \
			ft_strlen(newfile)) != 0)
			{
				free(newfile);
				return (NULL);
			}
		}
		if (redir && redir->type == SPC)
			redir = redir->next;
		free(newfile);
	}
	return (joined);
}

int	expandable_tkn(t_token *lst)
{
	if (!*lst->lexeme)
		return (0);
	while (lst && !is_redir_in(lst->type) && !is_redir_out(lst->type))
		lst = lst->prev;
	if (lst && (lst->type == HDOC || lst->type == HDOC_EXP))
		return (0);
	return (1);
}
