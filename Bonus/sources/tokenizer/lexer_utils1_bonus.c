/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:31:45 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

t_token	*new_token_node(t_node_type type, char *content, size_t size)
{
	t_token	*node;

	node = (t_token *)ft_malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->lexeme = (char *)ft_malloc((size + 1) * sizeof(char));
	if (!node->lexeme)
		return (NULL);
	ft_strlcpy(node->lexeme, content, size + 1);
	node->type = type;
	node->next = NULL;
	return (node);
}

int	token_list_add(t_token **list, t_node_type type, char *content, size_t size)
{
	t_token	*tmp;

	tmp = *list;
	if (!tmp)
	{
		*list = new_token_node(type, content, size);
		tmp = *list;
		if (tmp)
			tmp->prev = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token_node(type, content, size);
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (1);
	return (0);
}

t_token	*lst_last(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

int	in_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	redir_syntax_error(char *cmdline)
{
	if (!cmdline[0])
		print_syntax_error(UNEX_TOK, "newline");
	else if (!ft_strncmp(cmdline, "||", 2))
		print_syntax_error(UNEX_TOK, "||");
	else if (cmdline[0] == '|')
		print_syntax_error(UNEX_TOK, "|");
	else if (!ft_strncmp(cmdline, "&&", 2))
		print_syntax_error(UNEX_TOK, "&&");
	else if (cmdline[0] == '&')
		return (0);
	else if (cmdline[0] == '(')
		print_syntax_error(UNEX_PAREN, NULL);
	else if (cmdline[0] == ')')
		print_syntax_error(UNEX_RPAR, NULL);
	else if (!ft_strncmp(cmdline, ">>", 2))
		print_syntax_error(UNEX_TOK, ">>");
	else if (cmdline[0] == '>')
		print_syntax_error(UNEX_TOK, ">");
	else if (!ft_strncmp(cmdline, "<<", 2))
		print_syntax_error(UNEX_TOK, "<<");
	else if (cmdline[0] == '<')
		print_syntax_error(UNEX_TOK, "<");
	g_exit.status = SYNTAXERR;
	return (1);
}
