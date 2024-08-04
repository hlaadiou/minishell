/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:31:45 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 00:41:12 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_heredoc(t_token **tokens, char *cmdline)
{
	int		start;
	int		size;
	t_token	*last;

	start = 2;
	while (cmdline[start] && in_set(cmdline[start], BLANK))
		start++;
	if (!cmdline[start] || in_set(cmdline[start], HDOC_SEP))
	{
		if (redir_syntax_error(&cmdline[start]) != 0)
			return (-1);
	}
	size = check_tokens(tokens, cmdline + start, SEPARATOR);
	if (size < 0)
		return (-1);
	last = lst_last(*tokens);
	if (last->type != WORD)
		last->type = HDOC;
	else
		last->type = HDOC_EXP;
	return (start + size);
}

int	check_append(t_token **tokens, char *cmdline)
{
	t_token	*last;
	int		start;
	int		size;

	start = 2;
	size = 0;
	while (cmdline[start] && in_set(cmdline[start], BLANK))
		start++;
	if (!cmdline[start] || in_set(cmdline[start], HDOC_SEP))
	{
		if (redir_syntax_error(&cmdline[start]) != 0)
			return (-1);
	}
	size = check_tokens(tokens, cmdline + start, SEPARATOR);
	if (size < 0)
		return (-1);
	last = lst_last(*tokens);
	if (last->type == S_QUOTE)
		last->type = APPEND_SQ;
	else if (last->type == D_QUOTE)
		last->type = APPEND_DQ;
	else
		last->type = APPEND_WD;
	return (start + size);
}

int	check_infile(t_token **tokens, char *cmdline)
{
	t_token	*last;
	int		start;
	int		size;

	start = 1;
	size = 0;
	while (cmdline[start] && in_set(cmdline[start], BLANK))
		start++;
	if (!cmdline[start] || in_set(cmdline[start], HDOC_SEP))
	{
		if (redir_syntax_error(&cmdline[start]) != 0)
			return (-1);
	}
	size = check_tokens(tokens, cmdline + start, SEPARATOR);
	if (size < 0)
		return (-1);
	last = lst_last(*tokens);
	if (last->type == S_QUOTE)
		last->type = RD_IN_SQ;
	else if (last->type == D_QUOTE)
		last->type = RD_IN_DQ;
	else
		last->type = RD_IN_WD;
	return (start + size);
}

int	check_outfile(t_token **tokens, char *cmdline)
{
	t_token	*last;
	int		start;
	int		size;

	start = 1;
	size = 0;
	while (cmdline[start] && in_set(cmdline[start], BLANK))
		start++;
	if (!cmdline[start] || in_set(cmdline[start], HDOC_SEP))
	{
		if (redir_syntax_error(&cmdline[start]) != 0)
			return (-1);
	}
	size = check_tokens(tokens, cmdline + start, SEPARATOR);
	if (size < 0)
		return (-1);
	last = lst_last(*tokens);
	if (last->type == S_QUOTE)
		last->type = RD_OUT_SQ;
	else if (last->type == D_QUOTE)
		last->type = RD_OUT_DQ;
	else
		last->type = RD_OUT_WD;
	return (start + size);
}

int	check_redirection(t_token **tokens, char *cmdline)
{
	if (!ft_strncmp(cmdline, "<<", 2))
		return (check_heredoc(tokens, cmdline));
	else if (!ft_strncmp(cmdline, ">>", 2))
		return (check_append(tokens, cmdline));
	else if (cmdline[0] == '<')
		return (check_infile(tokens, cmdline));
	else
		return (check_outfile(tokens, cmdline));
}
