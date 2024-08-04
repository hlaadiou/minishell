/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:07:24 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 00:41:12 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_for_closing_paren(t_token **tok)
{
	while (*tok)
	{
		if ((*tok)->type == R_PAREN)
			return (0);
		*tok = (*tok)->next;
	}
	return (UNCLOSED);
}

int	check_left(t_token *paren)
{
	paren = paren->prev;
	if (paren && paren->type == SPC)
		paren = paren->prev;
	if (paren && paren->type != L_PAREN && !is_connector(paren))
		return (UNEX_PAREN);
	return (0);
}

int	check_right(t_token *paren, char **s)
{
	while (paren)
	{
		skip_redirs(&paren);
		if (paren && (paren->type == R_PAREN || is_connector(paren)))
			break ;
		else if (paren && paren->type == SPC)
			paren = paren->next;
		else if (paren)
		{
			*s = paren->lexeme;
			return (UNEX_TOK);
		}
	}
	return (0);
}

int	check_mid(t_token **tok, char **s)
{
	int	err;

	err = 0;
	while (*tok)
	{
		if ((*tok)->type == L_PAREN)
			err = check_paren(tok, s);
		else if ((*tok)->type == OR || (*tok)->type == AND
			|| (*tok)->type == PIPE)
		{
			err = check_connector(tok);
			*tok = (*tok)->next;
		}
		else if ((*tok)->type == R_PAREN)
			break ;
		else
			*tok = (*tok)->next;
		if (err != 0)
			return (err);
	}
	return (0);
}

int	check_paren(t_token **tok, char **s)
{
	t_token	*end;
	int		err;

	err = check_left(*tok);
	if (err != 0)
		return (err);
	skip(tok, L_PAREN);
	skip(tok, SPC);
	if (*tok && (*tok)->type == R_PAREN)
		return (UNEX_RPAR);
	else if (!*tok)
		return (UNEX_NL);
	err = check_mid(tok, s);
	if (err != 0)
		return (err);
	end = *tok;
	err = check_for_closing_paren(&end);
	if (err != 0)
		return (err);
	*tok = end->next;
	err = check_right(*tok, s);
	if (err != 0)
		return (err);
	*s = NULL;
	return (0);
}
