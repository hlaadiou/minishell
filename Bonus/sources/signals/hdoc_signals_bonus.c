/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_signals_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:04:12 by mmisskin          #+#    #+#             */
/*   Updated: 2023/08/21 14:46:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

void	hdoc_handler(int signum)
{
	if (signum == SIGINT)
		exit(EXIT_FAILURE);
}

void	heredoc_signals(void)
{
	struct sigaction	sig;

	sig.sa_handler = hdoc_handler; 
	sig.sa_flags = 0;
	sigemptyset(&sig.sa_mask);
	if (sigaction(SIGINT, &sig, NULL) == -1)
		perror(NULL);
	sig.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sig, NULL) == -1)
		perror(NULL);
}
