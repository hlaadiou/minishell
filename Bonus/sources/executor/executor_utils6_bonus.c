/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils6_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:30:40 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

char	*cmd_prefix(char *lexeme, t_env *envp)
{
	char	**paths;
	char	*cmd_abs;
	char	*path;
	size_t	i;

	i = 0;
	cmd_abs = NULL;
	if (is_a_directory(lexeme))
		exit(126);
	paths = ft_split(get_env_value(envp, "PATH"), ":");
	while (paths && paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		cmd_abs = ft_strjoin(path, lexeme);
		free(path);
		if (access(cmd_abs, F_OK) == -1)
		{
			free(cmd_abs);
			i++;
		}
		else
			break ;
	}
	throw_error(paths, cmd_abs, lexeme, i);
	return (clean_vec(paths), cmd_abs);
}

char	*check_path(char *lexeme, t_env *envp)
{
	if (lexeme && (!ft_strncmp(lexeme, "/", 1) || !ft_strncmp(lexeme, "./", 2) \
		|| !ft_strncmp(lexeme, "../", 3)))
	{
		if (access(lexeme, F_OK) == 0)
		{
			if (access(lexeme, X_OK) == -1)
			{
				cmd_error(lexeme);
				exit(126);
			}
		}
		else
		{
			cmd_error(lexeme);
			exit(127);
		}
		if (is_a_directory(lexeme))
			exit(126);
		return (ft_strdup(lexeme));
	}
	return (cmd_prefix(lexeme, envp));
}

char	**build_vec(t_token *list, t_env *envp)
{
	size_t	i;
	size_t	words;
	char	**vec;

	i = 0;
	vec = NULL;
	words = count_words(list) + 1;
	vec = (char **)ft_malloc(words * sizeof(char *));
	if (!vec)
		return (NULL);
	vec[i++] = check_path(list->lexeme, envp);
	if (!vec[0])
		return (NULL);
	list = list->next;
	while (list && i < words)
	{
		vec[i++] = list->lexeme;
		list = list->next;
	}
	vec[i] = NULL;
	return (vec);
}

char	**build_env_vec(t_env *env)
{
	size_t	i;
	size_t	words;
	char	**vec;
	char	*joined;

	i = 0;
	words = env_size(env) + 1;
	vec = (char **)malloc(words * sizeof(char *));
	if (!vec)
		return (NULL);
	while (env && i < words)
	{
		if (env && env->value && !env->hide)
		{
			joined = ft_strjoin(env->name, "=");
			vec[i] = ft_strjoin(joined, env->value);
			free(joined);
			i++;
		}
		env = env->next;
	}
	vec[i] = NULL;
	return (vec);
}

char	**build_builtin_vec(t_token *cmd)
{
	size_t	i;
	size_t	size;
	char	**vec;

	i = 0;
	size = tkn_lst_size(cmd) + 1;
	vec = (char **)malloc(size * sizeof(char *));
	if (!vec)
		return (NULL);
	while (i < size - 1)
	{
		vec[i] = ft_strdup(cmd->lexeme);
		i++;
		cmd = cmd->next;
	}
	vec[i] = NULL;
	return (vec);
}
