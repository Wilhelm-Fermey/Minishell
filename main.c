/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:07:54 by zkansoun          #+#    #+#             */
/*   Updated: 2022/05/31 13:51:34 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_seg	**take_tokens(char **segments)
{
	t_seg	**seg;
	t_seg	*temp;
	int		i;

	i = 0;
	seg = malloc(sizeof(t_seg *));
	if (!seg)
		return (NULL);
	*seg = malloc(sizeof(t_seg));
	if (!*seg)
		return (NULL);
	(*seg)->next = NULL;
	temp = *seg;
	while (segments[i])
	{
		temp->tokens = ft_split_quotes(segments[i], ' ');
		if (segments[i + 1])
			add_list(seg);
		temp = temp->next;
		i++;
	}
	return (seg);
}

int	ft_init(t_seg   **seg, char **path, char *line)
{
	(void)	line;
	fill_cmd(seg, path);
	if (check_seg(seg))
		return (1);
	fill_input(seg);
	fill_output(seg);
	fill_flags(seg);
	fill_args(seg);
	replace_var(seg, g_envp);
	check_args(seg);
	return (0);
}

int	prompt(char **path)
{
	t_seg	**seg;
	char	**segments;
	char	*line;

	run_signals(1);
	line = readline("\033[0;36mMinishell $> \e[0m");
	while (line)
	{
		if (*line && ft_line_space(line))
		{
			add_history(line);
			segments = ft_split_quotes(line, '|');
			seg = take_tokens(segments);
			if (!ft_init(seg, path, line))
			{
				ft_pipex(seg, path);
				free(seg);
			}
			free (line);
		}
		line = readline("\033[0;36mMinishell $> \e[0m");
	}
	return (0);
}

void	fill_envp(char **envp)
{
	int		i;
	t_list	*tmp;
	char	*exit_status;

	g_envp = malloc(sizeof(t_list *));
	if (!g_envp)
		printf("Error malloc\n");
	exit_status = ft_strdup("?=0");
	*g_envp = ft_lstnew((void *)(exit_status));
	i = 0;
	while (envp[i])
	{
		tmp = ft_lstnew(ft_substr(envp[i], 0, ft_strlen(envp[i])));
		ft_lstadd_back(g_envp, tmp);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**path;
	int		i;

	(void) argv;
	(void) argc;
	i = -1;
	path = ft_split(getenv("PATH"), ':');
	while (path[++i])
			path[i] = ft_strjoin(path[i], "/");
	fill_envp(envp);
	prompt(path);
}
