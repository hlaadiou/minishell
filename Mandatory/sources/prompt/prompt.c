/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:22:07 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 00:21:25 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*prompt(t_env *env)
{
	char	*prompt;
	char	*cwd;
	char	*home;
	size_t	len;

	cwd = getcwd(NULL, 0);
	home = get_env_value(env, "HOME");
	if (!home || !cwd)
		return (free(cwd), ft_strdup("minishell-1.0$ "));
	len = ft_strlen(home);
	if (!ft_strncmp(cwd, home, len))
	{
		prompt = ft_strjoin("~", cwd + len);
		free(cwd);
		cwd = prompt;
		prompt = ft_strjoin(cwd, "$ ");
		free(cwd);
		return (prompt);
	}
	prompt = ft_strjoin(cwd, "$ ");
	free(cwd);
	return (prompt);
}
