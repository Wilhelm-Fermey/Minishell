/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_seg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilhelmfermey <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:01:19 by wilhelmfermey     #+#    #+#             */
/*   Updated: 2022/05/31 13:37:20 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quote(char *line)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			x++;
		else if (line[i] == '\"')
			y++;
		i++;
	}
	if (x % 2 == 0 && y % 2 == 0)
		return (1);
	printf("Quotes must be closed");
	return (0);
}

int	ft_check_one_arg(char *line)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	if (!ft_quote(line))
		return (0);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			x++;
		if (line[i] == '|' && x % 2 == 1)
			y++;
		i++;
	}
	if (y)
		return (1);
	return (0);
}

void	ft_one_arg(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\'' && line[i] != '\"')
		i++;
	while (line[i])
	{
		if (line[i] != '\'' && line[i] != '\"')
			printf("%c",line[i]);
		i++;
	}
	printf("\n");
}
