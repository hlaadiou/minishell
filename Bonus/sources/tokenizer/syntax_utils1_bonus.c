/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils1_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:07:24 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	print_error(char *s1, char *s2)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
		ft_putstr_fd(s2, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	is_connector(t_token *tok)
{
	if (tok->type == OR || tok->type == AND || tok->type == PIPE)
		return (1);
	return (0);
}

int	is_cmd(t_token *tok)
{
	if (!is_redir_in(tok->type) && !is_redir_out(tok->type)
		&& !is_connector(tok))
		return (1);
	return (0);
}

void	print_syntax_error(int err, char *str)
{
	if (err == UNCLOSED)
		print_error("minishell: unexpected EOF while looking for matching: ",
			")");
	else if (err == UNEX_PIPE)
		print_error("minishell: syntax error near unexpected token: ", "|");
	else if (err == UNEX_OR)
		print_error("minishell: syntax error near unexpected token: ", "||");
	else if (err == UNEX_AND)
		print_error("minishell: syntax error near unexpected token: ", "&&");
	else if (err == UNEX_RPAR)
		print_error("minishell: syntax error near unexpected token: ", ")");
	else if (err == UNEX_NL)
		print_error("minishell: syntax error near unexpected token: ",
			"newline");
	else if (err == UNEX_PAREN)
		print_error("minishell: syntax error near unexpected token: ", "(");
	else if (err == UNEX_TOK)
		print_error("minishell: syntax error near unexpected token: ", str);
	g_exit.status = SYNTAXERR;
}
