/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfermey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:11:29 by wfermey           #+#    #+#             */
/*   Updated: 2022/05/31 10:27:04 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_cmd(t_seg **seg, char **path)
{
	t_seg	*temp;
	int		i[3];

	temp = *seg;
	while (temp)
	{
		temp->cmd = NULL;
		i[0] = -1;
		while (temp->tokens[++i[0]])
		{
			i[1] = -1;
			i[2] = 0;
			if (strcmp(temp->tokens[i[0]], "cd") == 0)
			{
				temp->cmd = ft_substr("cd", 0, 2);
				break ;
			}
			if (strcmp(temp->tokens[i[0]], "export") == 0)
			{
				temp->cmd = ft_substr("export", 0, 6);
				break ;
			}
			if (strcmp(temp->tokens[i[0]], "unset") == 0)
			{
				temp->cmd = ft_substr("unset", 0, 5);
				break ;
			}
			if (strcmp(temp->tokens[i[0]], "exit") == 0)
			{
				temp->cmd = ft_substr("exit", 0, 4);
				break ;
			}
			while (path[++i[1]])
			{
				if (!access(ft_strjoin(path[i[1]], temp->tokens[i[0]]), F_OK))
				{
					temp->cmd = temp->tokens[i[0]];
					i[2] = 1;
					break ;
				}
			}
			if (i[2] == 1)
				break ;
		}
		temp = temp->next;
	}
}

void	fill_flags(t_seg **seg)
{
	t_seg	*temp;
	int		i;

	temp = *seg;
	while (temp)
	{
		temp->flags = NULL;
		i = -1;
		while (temp->tokens[++i])
		{
			if (temp->tokens[i][0] == '-')
			{
				if (temp->flags == NULL)
					temp->flags = ft_strdup(temp->tokens[i]);
				else
				{
					temp->flags = ft_strjoin(temp->flags, temp->tokens[i] + 1);
				}
			}
		}
		temp = temp->next;
	}
}

void    fill_input(t_seg **seg)
{
	t_seg	*tmp;
	int		i;

	tmp = *seg;
	while (tmp)
	{
		i = -1;
		tmp->input = malloc(sizeof(char *));
		if (tmp->input == NULL)
			printf("Error malloc\n");
		tmp->input[0] = NULL;
		while (tmp->tokens[++i])
		{
			if ((tmp->tokens[i][0] == '<' && tmp->tokens[i][1] == '\0')
				|| (tmp->tokens[i][0] == '<' && tmp->tokens[i][1] == '<'
				&& tmp->tokens[i][2] == '\0'))
			{
				if (tmp->tokens[i][1] != '<')
					tmp->input = add_line_end(tmp->input, ft_strjoin("1", tmp->tokens[i + 1]));
				else
					tmp->input = add_line_end(tmp->input, ft_strjoin("2", tmp->tokens[i + 1]));
			}
			if ((tmp->tokens[i][0] == '<' && tmp->tokens[i][1] != '\0'
				&& tmp->tokens[i][1] != '<') || (tmp->tokens[i][0] == '<'
				&& tmp->tokens[i][1] == '<' && tmp->tokens[i][2] != '\0'))
				{
					if (tmp->tokens[i][1] == '<')
						tmp->input = add_line_end(tmp->input, ft_strjoin("2", tmp->tokens[i] + 2));
					else
						tmp->input = add_line_end(tmp->input, ft_strjoin("1", tmp->tokens[i] + 1));
				}

		}
		tmp = tmp->next;
	}
}

void    fill_output(t_seg **seg)
{
	t_seg	*tmp;
	int		i;

	tmp = *seg;
	while (tmp)
	{
		i = -1;
		tmp->output = malloc(sizeof(char *));
		if (tmp->output == NULL)
			printf("Error malloc");
		tmp->output[0] = NULL;
		while (tmp->tokens[++i])
		{
			if ((tmp->tokens[i][0] == '>' && tmp->tokens[i][1] == '\0')
				|| (tmp->tokens[i][0] == '>' && tmp->tokens[i][1] == '>'
				&& tmp->tokens[i][2] == '\0'))
			{
				if(tmp->tokens[i][1] == '>')
					tmp->output = add_line_end(tmp->output, ft_strjoin("2", tmp->tokens[i + 1]));
				else
					tmp->output = add_line_end(tmp->output, ft_strjoin("1", tmp->tokens[i + 1]));
			}
			if ((tmp->tokens[i][0] == '>' && tmp->tokens[i][1] != '\0'
				&& tmp->tokens[i][1] != '>') || (tmp->tokens[i][0] == '>'
				&& tmp->tokens[i][1] == '>' && tmp->tokens[i][2] != '\0'))
			{
				if (tmp->tokens[i][1] == '>')
					tmp->output = add_line_end(tmp->output, ft_strjoin("2", tmp->tokens[i] + 2));
				else
					tmp->output = add_line_end(tmp->output, ft_strjoin("1", tmp->tokens[i] + 1));
			}

		}
		tmp = tmp->next;
	}
}

int	ft_is_not_inout(char *str, t_seg *seg)
{
	t_seg *tmp;
	int	i;

	tmp = seg;
	i = -1;
	while (tmp->input[++i])
	{
		if (!ft_strcmp(tmp->input[i] + 1, str))
			return (-1);
	}
	i = -1;
	while (tmp->output[++i])
	{
		if (!ft_strcmp(tmp->output[i] + 1, str))
			return (-1);
	}
	return (0);
}

void	fill_args(t_seg **seg)
{
	t_seg	*tmp;
	int		i;

	tmp = *seg;
	while (tmp)
	{
		tmp->args = malloc(sizeof(char *));
		if (tmp->args == NULL)
			printf("Error malloc");
		tmp->args[0] = NULL;
		i = 0;
		while (ft_strcmp(tmp->tokens[i], tmp->cmd))
			i++;
		while (tmp->tokens[i])
		{
			if (ft_strcmp(tmp->tokens[i], tmp->cmd) && tmp->tokens[i][0] != '-'
				&& tmp->tokens[i][0] != '>' && tmp->tokens[i][0] != '<'
				&& !ft_is_not_inout(tmp->tokens[i], tmp))
				tmp->args = add_line_end(tmp->args, tmp->tokens[i]);

			i++;
		}
		tmp = tmp->next;
	}
}
