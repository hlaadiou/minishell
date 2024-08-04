/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils5_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:33:12 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

int	is_append(t_node_type type)
{
	if (type == APPEND_WD || type == APPEND_DQ || type == APPEND_SQ)
		return (1);
	return (0);
}

int	is_rd_in(t_node_type type)
{
	if (type == RD_IN_WD || type == RD_IN_DQ || type == RD_IN_SQ)
		return (1);
	return (0);
}

int	is_rd_out(t_node_type type)
{
	if (type == RD_OUT_WD || type == RD_OUT_DQ || type == RD_OUT_SQ)
		return (1);
	return (0);
}

int	is_hdoc(t_node_type type)
{
	if (type == HDOC || type == HDOC_EXP)
		return (1);
	return (0);
}

int	is_builtin(t_token *cmd)
{
	if (cmd && cmd->lexeme)
	{
		if (!ft_strcmp(cmd->lexeme, "cd") \
			|| !ft_strcmp(cmd->lexeme, "echo") \
			|| !ft_strcmp(cmd->lexeme, "pwd") \
			|| !ft_strcmp(cmd->lexeme, "export") \
			|| !ft_strcmp(cmd->lexeme, "unset") \
			|| !ft_strcmp(cmd->lexeme, "env") \
			|| !ft_strcmp(cmd->lexeme, "exit"))
			return (1);
	}
	return (0);
}
