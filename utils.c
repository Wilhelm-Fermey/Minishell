/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:59:50 by zkansoun          #+#    #+#             */
/*   Updated: 2022/05/31 13:41:30 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen2(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin2(char *str, char *buff)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(ft_strlen2(str) + ft_strlen2(buff) + 1);
	if (!res)
		return (NULL);
	if (str)
	{
		while (str[i])
		{
			res[i] = str[i];
			i++;
		}
	}
	while (buff[j])
		res[i++] = buff[j++];
	res[i] = '\0';
	free(str);
	return (res);
}

int		ft_lstsize2(t_seg **lst)
{
	int			i;
	t_seg		*tmp;

	tmp = *lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char *ft_strstr(char *str, char *to_find)
{
	int i;
	int j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (str + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_args(char **strr, char *str)
{
	int	i;

	i = 0;
	while (strr[i])
	{
		if (!ft_strcmp(strr[i], str))
			return (0);
		i++;
	}
	return (1);
}
