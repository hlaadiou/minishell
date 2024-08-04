/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:04:12 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 00:20:30 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit.status = 1;
	}
}

void	default_signals(void)
{
	struct sigaction	sig;

	sig.sa_handler = SIG_DFL;
	sig.sa_flags = 0;
	sigemptyset(&sig.sa_mask);
	if (sigaction(SIGINT, &sig, NULL) == -1)
		perror(NULL);
	if (sigaction(SIGQUIT, &sig, NULL) == -1)
		perror(NULL);
}

void	ignore_signals(void)
{
	struct sigaction	sig;

	sig.sa_handler = SIG_IGN;
	sig.sa_flags = 0;
	sigemptyset(&sig.sa_mask);
	if (sigaction(SIGINT, &sig, NULL) == -1)
		perror(NULL);
	if (sigaction(SIGQUIT, &sig, NULL) == -1)
		perror(NULL);
}

void	signal_interrupter(void)
{
	struct sigaction	sig;

	sig.sa_handler = sig_handler;
	sig.sa_flags = 0;
	sigemptyset(&sig.sa_mask);
	if (sigaction(SIGINT, &sig, NULL) == -1)
		perror(NULL);
	sig.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sig, NULL) == -1)
		perror(NULL);
}
