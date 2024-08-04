/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 02:04:37 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

t_token	*read_heredoc(char *delim)
{
	t_token	*doc;
	char	*line;
	char	*joined;

	doc = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delim))
		{
			free(line);
			break ;
		}
		joined = ft_strjoin(line, "\n");
		if (token_list_add(&doc, WORD, joined, ft_strlen(line) + 1) != 0)
			return (NULL);
		if (token_list_add(&doc, SPC, " ", 1) != 0)
			return (NULL);
		free(joined);
		free(line);
	}
	return (doc);
}

void	update_subshell_hdoc(t_tree *root, int subsh_hdoc)
{
	if (root->type != T_CMD && root->type != S_CMD)
	{
		update_subshell_hdoc(root->node.lchild, subsh_hdoc);
		update_subshell_hdoc(root->node.rchild, subsh_hdoc);
	}
	else
		root->cmd.sub_hdoc = subsh_hdoc;
}

t_token	*heredoc_content_exp(t_token *doc, t_env *env)
{
	t_token	*newdoc;

	newdoc = NULL;
	if (env)
	{
		if (expand_env_vars(&newdoc, doc, env) == 1)
			return (NULL);
		newdoc = tkn_join(newdoc);
	}
	return (newdoc);
}

void	heredoc(t_token *hdoc, t_env *env, int *pipe)
{
	t_token	*doc;

	heredoc_signals();
	doc = read_heredoc(hdoc->lexeme);
	if (hdoc->type == HDOC_EXP)
		doc = heredoc_content_exp(doc, env);
	while (doc)
	{
		if (doc->type != SPC)
			write(pipe[1], doc->lexeme, ft_strlen(doc->lexeme));
		doc = doc->next;
	}
	close(pipe[0]);
	close(pipe[1]);
	clean_all();
	exit(0);
}

int	open_heredoc(t_token *hdoc, t_env *env)
{
	int		end[2];
	pid_t	pid;

	if (pipe(end) == -1)
	{
		ft_putstr_fd("Heredoc pipe failed\n", STDERR_FILENO);
		return (-1);
	}
	pid = _fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		heredoc(hdoc, env, end);
	else
	{
		ignore_signals();
		waitpid(pid, &g_exit.status, 0);
		signal_interrupter();
		close(end[1]);
		g_exit.status = WEXITSTATUS(g_exit.status);
		if (g_exit.status == 1)
			return (close(end[0]), -1);
	}
	return (end[0]);
}
