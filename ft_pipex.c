/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilhelmfermey <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:23:01 by wilhelmfermey     #+#    #+#             */
/*   Updated: 2022/05/31 13:29:15 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check(t_seg **seg, char *line)
{
	t_seg	*tmp;
	int		i;
	int		x;
	int		y;

	tmp = *seg;
	i = 0;
	x = 0;
	y = 0;
	if (!tmp->cmd)
		return (printf("Command not found\n"));
	while (line[i])
	{
		if (line[i] == '<')
			x++;
		else if (line[i] == '>')
			y++;
		i++;
	}
	if (x && !tmp->input[0])
		return (printf("Parse error\n"));
	else if (y && !tmp->output[0])
		return (printf("Parse error\n"));
	return (0);
}

int	ft_cmd(t_seg **seg, char **path)
{
	t_seg	*tmp;
	int		i;
	char	*cmd2;

	tmp = *seg;
	i = 0;
	while (path[i])
	{
		cmd2 = ft_strjoin(path[i], tmp->cmd);
		if (access(cmd2, F_OK) == 0)
		{
			tmp->cmd = cmd2;
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_choose(t_seg **seg, char **path)
{
	t_seg	*tmp;

	tmp = *seg;
	if (!ft_strcmp(tmp->cmd, "cd"))
	{	if (tmp->next)
			ft_pipe_builtin(&tmp);
		ft_cd(seg);
	}
	else if (!ft_strcmp(tmp->cmd, "echo"))
	{	if (tmp->next)
			ft_pipe_builtin(&tmp);
		ft_echo(seg);
	}
	else if (!ft_strcmp(tmp->cmd, "pwd"))
	{	if (tmp->next)
			ft_pipe_builtin(&tmp);
		ft_pwd(seg);
	}
	else if (!ft_strcmp(tmp->cmd, "export"))
	{	if (tmp->next)
			ft_pipe_builtin(&tmp);
		ft_export(seg);
	}
	else if (!ft_strcmp(tmp->cmd, "unset"))
	{	if (tmp->next)
			ft_pipe_builtin(&tmp);
		ft_unset(seg);
	}
	else if (!ft_strcmp(tmp->cmd, "env"))
	{	if (tmp->next)
			ft_pipe_builtin(&tmp);
		ft_env(seg);
	}
	else if (!ft_strcmp(tmp->cmd, "exit"))
	{	if (tmp->next)
			ft_pipe_builtin(&tmp);
		ft_exit(seg);
	}
	else
		return (ft_cmd(seg, path));
	return (0);
}


void	ft_pipex(t_seg **seg, char **path)
{
	t_seg 	*tmp;
	int	fdd;
	int	pid;

	tmp = *seg;
	fdd = 0;
	pid = 0;
	while (tmp)
	{
		check_heredoc(&tmp);
		if (ft_choose(&tmp, path))
		{
			pipe(tmp->fd);
			tmp->array = ft_array(&tmp);
			if (tmp->input[0])
				merge_files(tmp->input, fdd);
			pid = fork();
			run_signals(2);
			if (pid == 0)
				ft_child(&tmp, &fdd);
			else
				ft_parents(&tmp, &fdd);
		}
		tmp = tmp->next;
	}
}
