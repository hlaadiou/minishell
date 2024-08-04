/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:54:02 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

static void	print_invalid_id(char *id)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(id, STDERR_FILENO);
	ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
}

char	*get_value(t_env *env, char *id, char *name)
{
	int		size;
	t_env	*old;

	size = 0;
	if (!name)
		return (NULL);
	while (id[size] && id[size] != '=')
		size++;
	old = get_env_node(env, name);
	if (!id[size] && old && old->value && old->hide <= 1)
	{
		old->hide = 0;
		return (ft_strdup(old->value));
	}
	if (!id[size])
		return (NULL);
	return (ft_strdup(id + size + 1));
}

static char	*check_identifier(char *arg, int *append)
{
	int		size;
	char	*name;

	size = 1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		size = -1;
	else
		size = check_name(arg, append);
	if (size < 0)
	{
		print_invalid_id(arg);
		g_exit.status = 1;
		return (NULL);
	}
	name = (char *)malloc((size + 1) * sizeof(char));
	if (!name)
		return (NULL);
	ft_strlcpy(name, arg, size + 1);
	return (name);
}

static int	check_arguments(char **cmd)
{
	int	i;

	i = 1;
	g_exit.status = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i][0] == '-')
		{
			ft_putstr_fd("minishell: export: ", STDERR_FILENO);
			write(STDERR_FILENO, cmd[i], 2);
			ft_putstr_fd(": invalid option\n", STDERR_FILENO);
			ft_putstr_fd("export: usage: export [name[=value] ...]\n", \
			STDERR_FILENO);
			g_exit.status = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

void	_export(char **cmd, t_env **env, int fd)
{
	int		i;
	int		app;
	char	*name;
	char	*value;

	i = 0;
	if (check_arguments(cmd) != 0)
		return ;
	if (!cmd[1])
		print_env(*env, fd);
	else
	{
		while (cmd[++i])
		{
			app = 0;
			name = check_identifier(cmd[i], &app);
			value = get_value(*env, cmd[i], name);
			if (value && name)
				update_env_value(env, ft_strdup(name), ft_strdup(value), app);
			else if (name)
				update_env_value(env, ft_strdup(name), value, app);
			free(value);
			free(name);
		}
	}
}
