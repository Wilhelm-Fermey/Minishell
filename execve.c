/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilhelmfermey <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:39:27 by wilhelmfermey     #+#    #+#             */
/*   Updated: 2022/05/31 13:23:01 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe_builtin(t_seg **seg)
{
	int		i;
	t_seg	*tmp;
	int		fd;
	
	i = 0;
	tmp = *seg;
	fd = open(".PIPE", O_RDWR | O_CREAT | O_TRUNC, 0644);
	close (fd);
	while (tmp->output[i])
		i++;
	tmp->output[i] = ft_strjoin("1", ".PIPE");
	i = 0;
	tmp = tmp->next;
	if (tmp->input[0])
		tmp->input = add_line(tmp->input, "1.PIPE");
	else
		tmp->input[0] = ft_strjoin("1", ".PIPE");
}

void	 ft_child(t_seg **res, int *fdd)
{
	t_seg	*tmp;
	int		input;

	tmp = *res;
	if (tmp->input[0])
		input = open(".total_data", O_RDONLY, 0644);
	else 
		input = *fdd;
	dup2(input, 0);
	if (tmp->next != NULL || tmp->output[0])
		dup2(tmp->fd[1], 1);
	close(tmp->fd[1]);
	execve(tmp->cmd, tmp->array, NULL);
	exit(0);
}

void	ft_parents(t_seg **res, int *fdd)
{
	t_seg	*tmp;
	int		status;
	char	buff;
	int		out_fd;

	tmp = *res;
	waitpid(0, &status, 0);
	update_exit_code(ft_itoa(WEXITSTATUS(status)));
	close(tmp->fd[1]);
	*fdd = tmp->fd[0];
	if (tmp->output[0])
	{
		out_fd = open(".PIPE", O_RDWR | O_CREAT | O_TRUNC, 0644);
		while (	read(*fdd, &buff, 1) > 0)
			write(out_fd, &buff, 1);
		close (out_fd);
		close (*fdd);
		if (tmp->next)
			tmp->next->input = add_line(tmp->next->input, "1.PIPE");
		*fdd = 0;
		handle_all_out(tmp->output);
	}
}

