/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:31:45 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

int	check_single_quotes(t_token **tokens, char *cmdline)
{
	t_token	*last;
	int		i;
	int		size;

	i = 0;
	while (cmdline[i] && cmdline[i] != '\'')
		i++;
	if (!cmdline[i])
	{
		ft_putstr_fd("minishell: unclosed single quotes\n", STDERR_FILENO);
		g_exit.status = SYNTAXERR;
		return (-1);
	}
	size = check_word(tokens, cmdline, "'");
	if (size < 0)
		return (-1);
	else
	{
		last = lst_last(*tokens);
		last->type = S_QUOTE;
	}
	return (i + 2);
}

int	check_double_quotes(t_token **tokens, char *cmdline)
{
	t_token	*last;
	int		i;
	int		size;

	i = 0;
	while (cmdline[i] && cmdline[i] != '"')
		i++;
	if (!cmdline[i])
	{
		ft_putstr_fd("minishell: unclosed double quotes\n", STDERR_FILENO);
		g_exit.status = SYNTAXERR;
		return (-1);
	}
	size = check_word(tokens, cmdline, "\"");
	if (size < 0)
		return (-1);
	else
	{
		last = lst_last(*tokens);
		last->type = D_QUOTE;
	}
	return (i + 2);
}

int	check_tokens(t_token **tokens, char *cmdline, char *limit)
{
	int	size;

	size = 0;
	if (cmdline[0] == '(' || cmdline[0] == ')')
		size = check_parenthesis(tokens, cmdline);
	else if (cmdline[0] == '|')
	{
		if (cmdline[1] == '|')
			size = check_or(tokens, cmdline);
		else
			size = check_pipe(tokens, cmdline);
	}
	else if (cmdline[0] == '&')
		size = check_and(tokens, cmdline);
	else if (in_set(cmdline[0], "<>"))
		size = check_redirection(tokens, cmdline);
	else if (cmdline[0] == '\'')
		size = check_single_quotes(tokens, cmdline + 1);
	else if (cmdline[0] == '"')
		size = check_double_quotes(tokens, cmdline + 1);
	else
		size = check_word(tokens, cmdline, limit);
	return (size);
}

t_token	*lexer(char *cmdline)
{
	t_token	*tokens;
	int		i;
	int		skip;

	i = 0;
	tokens = NULL;
	while (cmdline[i])
	{
		skip = 0;
		if (cmdline[i] && in_set(cmdline[i], BLANK))
		{
			while (cmdline[i] && in_set(cmdline[i], BLANK))
				i++;
			if (token_list_add(&tokens, SPC, " ", 1) != 0)
				return (NULL);
		}
		skip = check_tokens(&tokens, cmdline + i, SEPARATOR);
		if (skip < 0)
			return (NULL);
		i += skip;
	}
	check_syntax(&tokens);
	return (tokens);
}
