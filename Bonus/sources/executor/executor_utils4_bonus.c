/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils4_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:35:27 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

int	open_append_files(t_token *redir, int **fildes)
{
	int	tmpfd;

	if (is_append(redir->type))
	{
		tmpfd = open(redir->lexeme, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (tmpfd == -1)
			return (_error(redir->lexeme), 1);
		if ((*fildes)[1] != STDOUT_FILENO)
			close((*fildes)[1]);
		(*fildes)[1] = tmpfd;
	}
	return (0);
}

int	open_out_files(t_token *redir, int **fildes)
{
	int	tmpfd;

	if (is_rd_out(redir->type))
	{
		tmpfd = open(redir->lexeme, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (tmpfd == -1)
			return (_error(redir->lexeme), 1);
		if ((*fildes)[1] != STDOUT_FILENO)
			close((*fildes)[1]);
		(*fildes)[1] = tmpfd;
	}
	return (0);
}

int	open_in_files(t_token *redir, t_token **tmpredir)
{
	int	tmpfd;

	if (is_rd_in(redir->type))
	{
		tmpfd = open(redir->lexeme, O_RDONLY);
		if (tmpfd == -1)
			return (_error(redir->lexeme), 1);
		close(tmpfd);
		*tmpredir = redir;
	}
	return (0);
}

int	hdoc_or_rd_in(t_token *rdirlst, t_token *tmpredir, int **fildes)
{
	t_token	*redir;
	int		tmpfd;

	redir = lst_last(rdirlst);
	while (redir)
	{
		if (is_hdoc(redir->type))
			break ;
		else if (redir == tmpredir)
		{
			tmpfd = open(redir->lexeme, O_RDONLY);
			if (tmpfd == -1)
				return (_error(redir->lexeme), 1);
			if ((*fildes)[0] != STDIN_FILENO)
				close((*fildes)[0]);
			(*fildes)[0] = tmpfd;
		}
		redir = redir->prev;
	}
	return (0);
}

int	*open_files(t_cmd cmd)
{
	t_token	*redir;
	t_token	*tmpredir;
	int		*fildes;

	fildes = (int *)malloc(2 * sizeof(int));
	if (!fildes)
		return (NULL);
	redir = cmd.redir;
	tmpredir = NULL;
	default_fds(&fildes);
	if (cmd.hdoc != -1)
		fildes[0] = cmd.hdoc;
	while (redir)
	{
		if (open_append_files(redir, &fildes))
			return (NULL);
		else if (open_out_files(redir, &fildes))
			return (NULL);
		else if (open_in_files(redir, &tmpredir))
			return (NULL);
		redir = redir->next;
	}
	if (hdoc_or_rd_in(cmd.redir, tmpredir, &fildes))
		return (NULL);
	return (fildes);
}
