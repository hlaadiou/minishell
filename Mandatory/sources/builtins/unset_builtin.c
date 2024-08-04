/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:48:36 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 00:07:08 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_argument(char *cmd)
{
	if (cmd && cmd[0] == '-')
	{
		ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": invalid option\n", STDERR_FILENO);
		g_exit.status = 2;
		return (1);
	}
	return (0);
}

static void	print_invalid_id(char *id)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(id, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

static int	check_identifier(char *id)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	if (!ft_isalpha(id[0]) && id[0] != '_')
		err = 1;
	else
	{
		while (id[i])
		{
			if (!ft_isalnum(id[i]) && id[i] != '_')
			{
				err = 1;
				break ;
			}
			i++;
		}
	}
	if (err != 0)
	{
		print_invalid_id(id);
		return (1);
	}
	return (0);
}

void	delete_env_node(t_env **env, t_env *node)
{
	t_env	*prev;
	t_env	*next;

	prev = *env;
	next = node->next;
	while (prev && prev->next != node)
		prev = prev->next;
	if (*env == node)
		*env = next;
	else
		prev->next = next;
	free(node->name);
	free(node->value);
	free(node);
}

void	_unset(t_env **env, char **cmd)
{
	t_env	*node;
	int		i;

	i = 1;
	if (check_argument(cmd[1]) != 0)
		return ;
	while (cmd[i])
	{
		if (check_identifier(cmd[i]) == 0)
		{
			node = get_env_node(*env, cmd[i]);
			if (node)
				delete_env_node(env, node);
		}
		else
			g_exit.status = 1;
		i++;
	}
	g_exit.status = 0;
}
