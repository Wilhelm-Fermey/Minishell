/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilhelmfermey <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:22:46 by wilhelmfermey     #+#    #+#             */
/*   Updated: 2022/05/31 13:25:32 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_array_len(t_seg **seg)
{
	t_seg	*tmp;
	int		i;
	int		j;

	tmp = *seg;
	i = 0;
	j = 0;
	if (tmp->cmd)
		i++;
	if (tmp->flags)
		i++;
	if (tmp->args[0])
		while (tmp->args[j])
		{
			i++;
			j++;
		}
	return (i);
}

char	**ft_array(t_seg **seg)
{
	int		i;
	int		j;
	t_seg	*tmp;
	char 	**array;

	i = 0;
	tmp = *seg;
	array = malloc((ft_array_len(seg) + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	array[i] = ft_strdup(tmp->cmd);
	i++;
	if (tmp->flags)
	{
		array[i] = ft_strdup(tmp->flags);
		i++;
	}
	j = 0;
	if (tmp->args && tmp->args[0])
	{
		while (tmp->args[j])
			array[i++] = ft_strdup(tmp->args[j++]);
	}
	array[i] = NULL;
	return (array);
}
