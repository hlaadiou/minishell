/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:06:13 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	clean_exit(t_env **env, char *line)
{
	clean_env_list(env);
	clean_all();
	free(line);
	rl_on_new_line();
	rl_redisplay();
	printf("exit\n");
	exit(g_exit.status);
}

char	*trim_line(char *line)
{
	char	*cmdline;

	cmdline = ft_strtrim(line, BLANK);
	add_history(line);
	free(line);
	return (cmdline);
}

t_tree	*evaluate_cmd(char *cmdline)
{
	t_tree	*root;
	t_token	*tokens;

	tokens = lexer(cmdline);
	root = parser(&tokens);
	return (root);
}

void	minishell_loop(t_env *envp)
{
	t_tree		*root;
	char		*line;
	char		*cmdline;
	char		*shell;

	while (1)
	{
		shell = prompt(envp);
		line = readline(shell);
		free(shell);
		if (!line)
			clean_exit(&envp, line);
		else if (!*line)
		{
			free(line);
			continue ;
		}
		cmdline = trim_line(line);
		root = evaluate_cmd(cmdline);
		if (open_heredocs(root, envp) == 0)
			executor(root, &envp);
		free(cmdline);
		clean_all();
	}
}

int	main(int ac, char **av, char **env)
{
	t_env		*envp;

	if (ac != 1)
		return (1);
	envp = env_dup(av[0], env);
	if (!envp)
		return (1);
	signal_interrupter();
	minishell_loop(envp);
	clean_env_list(&envp);
}
