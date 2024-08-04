/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:07:24 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

int	check_before_con(t_token *tok)
{
	t_token	*ptr;

	ptr = tok->prev;
	while (ptr)
	{
		if (ptr->type == L_PAREN)
		{
			if (tok->type == PIPE)
				return (UNEX_PIPE);
			else if (tok->type == OR)
				return (UNEX_OR);
			else if (tok->type == AND)
				return (UNEX_AND);
		}
		else if (ptr->type == SPC)
			ptr = ptr->prev;
		else
			break ;
	}
	return (0);
}

int	check_after_con(t_token *ptr)
{
	while (ptr)
	{
		if (ptr->type == PIPE)
			return (UNEX_PIPE);
		else if (ptr->type == OR)
			return (UNEX_OR);
		else if (ptr->type == AND)
			return (UNEX_AND);
		else if (ptr->type == R_PAREN)
			return (UNEX_RPAR);
		else if (ptr->type == SPC)
			ptr = ptr->next;
		else
			break ;
	}
	if (!ptr)
		return (UNEX_NL);
	return (0);
}

int	check_connector(t_token **tok)
{
	int		err;

	err = check_before_con(*tok);
	if (err != 0)
		return (err);
	err = check_after_con((*tok)->next);
	if (err != 0)
		return (err);
	return (0);
}

void	check_syntax(t_token **tokens)
{
	t_token	*ptr;
	int		err;
	char	*str;

	ptr = *tokens;
	err = 0;
	while (ptr)
	{
		if (ptr->type == L_PAREN)
			err = check_paren(&ptr, &str);
		else if (ptr->type == OR || ptr->type == AND || ptr->type == PIPE)
			err = check_connector(&ptr);
		if (err != 0 || (ptr && ptr->type == R_PAREN))
		{
			if (err != 0)
				print_syntax_error(err, str);
			else
				print_syntax_error(UNEX_RPAR, NULL);
			*tokens = NULL;
			return ;
		}
		if (ptr)
			ptr = ptr->next;
	}
}
