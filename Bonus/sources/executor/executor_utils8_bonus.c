/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils8_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:24:21 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	_error(char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(file);
}

void	cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

void	cmd_error(char *lexeme)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(lexeme, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	is_a_directory(char *lexeme)
{
	struct stat	fstatus;

	if (stat(lexeme, &fstatus) == 0)
	{
		if (S_ISDIR(fstatus.st_mode))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(lexeme, STDERR_FILENO);
			ft_putstr_fd(": is a directory\n", STDERR_FILENO);
			return (1);
		}
	}
	return (0);
}

void	throw_error(char **paths, char *abs, char *lex, int i)
{
	if (!paths || !paths[i])
	{
		cmd_not_found(lex);
		exit(127);
	}
	if (access(abs, X_OK) == -1)
	{
		cmd_error(lex);
		exit(126);
	}
	return ;
}
