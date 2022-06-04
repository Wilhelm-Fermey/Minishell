/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilhelmfermey <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:03:50 by wilhelmfermey     #+#    #+#             */
/*   Updated: 2022/05/31 13:22:11 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_input2(t_seg **res, char *str)
{
	t_seg	*tmp;
	char	*heredoc;
	int		fd;

	tmp = *res;
	fd = open(".heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0664);
	heredoc = readline("heredoc> ");
	while (heredoc != NULL && ft_strcmp(heredoc, str))
	{
		ft_putstr_fd(heredoc, fd);
		ft_putstr_fd("\n", fd);
		heredoc = readline("heredoc> ");
	}
	close (fd);
	tmp->input = add_line(tmp->input, "1.heredoc");
}

void	check_heredoc(t_seg **seg)
{
	int		i;
	t_seg	*tmp;

	i = 0;
	tmp = *seg;
	while (tmp->input[i])
	{
		if (tmp->input[i][0] == '2')
		{
			ft_child_input2(seg, tmp->input[i] + 1);
			break ;
		}
		i++;
	}
}

void	ft_child_input(t_seg **res)
{
	t_seg	*tmp;
	int		fd;

	tmp = *res;
	fd = open(&tmp->input[0][1], O_RDONLY);
	if (fd < 0)
	{
		printf("%s: No such file or directory\n", &tmp->input[0][1]);
		exit(0);
	}
	dup2(fd, 0);
	if (tmp->next != NULL)
		dup2(tmp->fd[1], 1);
	close(tmp->fd[1]);
	execve(tmp->cmd, tmp->array, NULL);
	exit(0);
}

void	ft_child_output(t_seg **res, int *fdd)
{
	t_seg	*tmp;
	int		fd;

	tmp = *res;
	dup2(*fdd, 0);
	fd = open(tmp->output[0] + 1, O_RDWR | O_CREAT | O_TRUNC, 0644);
	int s = dup2(fd, 1);
	dprintf(2, "\niii%d\n", s);
	execve(tmp->cmd, tmp->array, NULL);
	exit(0);
}


