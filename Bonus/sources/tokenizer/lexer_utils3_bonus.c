/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:31:45 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

int	check_parenthesis(t_token **tokens, char *cmdline)
{
	if (cmdline[0] == '(')
	{
		if (token_list_add(tokens, L_PAREN, cmdline, 1) != 0)
			return (-1);
	}
	else if (cmdline[0] == ')')
	{
		if (token_list_add(tokens, R_PAREN, cmdline, 1) != 0)
			return (-1);
	}
	return (1);
}

int	check_or(t_token **tokens, char *cmdline)
{
	if (!*tokens)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token: ||\n",
			STDERR_FILENO);
		g_exit.status = SYNTAXERR;
		return (-1);
	}
	if (token_list_add(tokens, OR, cmdline, 2) != 0)
		return (-1);
	return (2);
}

int	check_and(t_token **tokens, char *cmdline)
{
	int		i;

	i = 0;
	while (cmdline[i] && cmdline[i] == '&')
		i++;
	if (i < 2)
	{
		if (token_list_add(tokens, WORD, cmdline, i) != 0)
			return (-1);
		return (i);
	}
	if (!*tokens)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token: &&\n",
			STDERR_FILENO);
		g_exit.status = SYNTAXERR;
		return (-1);
	}
	if (token_list_add(tokens, AND, cmdline, 2) != 0)
		return (-1);
	return (2);
}

int	check_pipe(t_token **tokens, char *cmdline)
{
	if (!*tokens)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token: |\n",
			STDERR_FILENO);
		g_exit.status = SYNTAXERR;
		return (-1);
	}
	if (token_list_add(tokens, PIPE, cmdline, 1) != 0)
		return (-1);
	return (1);
}

int	check_word(t_token **tokens, char *cmdline, char *limit)
{
	int			size;

	size = 0;
	while (cmdline[size] && !in_set(cmdline[size], limit))
		size++;
	if (token_list_add(tokens, WORD, cmdline, size) != 0)
		return (-1);
	return (size);
}
