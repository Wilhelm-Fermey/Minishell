/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilhelmfermey <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:46:53 by wilhelmfermey     #+#    #+#             */
/*   Updated: 2022/05/30 18:20:06 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_prompt(int sig)
{
		printf("\n");
		rl_on_new_line();
//		rl_replace_line("", 1);
		rl_redisplay();
		(void) sig;
}

void	ctrl_c(int sig)
{
	write(1, "\n", 1);
	(void) sig;
}

 void	run_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, ctrl_c);
	}
}
