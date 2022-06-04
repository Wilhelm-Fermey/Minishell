/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilhelmfermey <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:18:01 by wilhelmfermey     #+#    #+#             */
/*   Updated: 2022/05/31 13:41:14 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_line(char **tabb, char *str)
{
	int	i;
	int	j;
	char	**new_tab;
	char	*tmp;

	i = 0;
	while (tabb[i])
		i++;
	new_tab = malloc((i + 2) * sizeof(char *));
	if (new_tab)
		return (NULL);
	j = 1; 
	if(!ft_strcmp(tabb[0], "1.PIPE"))
	{
		free(tabb[0]);
		tabb[0] = ft_substr(str, 0, ft_strlen(str));
		tmp = ft_substr("1.PIPE", 0, 6);
		new_tab[0] = ft_substr(tmp, 0, ft_strlen(tmp));
	}
	else
		new_tab[0] = ft_substr(str, 0, ft_strlen(str));
	while (j < i + 1)
	{
		new_tab[j] = ft_substr(tabb[j - 1], 0, ft_strlen(tabb[j - 1]));
		j++;
	}
	new_tab[j] = NULL;
	free_table(tabb);
	return (new_tab);

}

void	ft_print_list(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		printf("%s\n", (char *)(tmp->content));
		tmp = tmp->next;
	}
}

void	del_content(t_list **head, char *content)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *head;
	prev = *head;
	while (tmp
		&& ft_strncmp((char *)tmp->content, content, ft_strlen(content)))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		prev->next = tmp->next;
		tmp->next = NULL;
		ft_lstdelone(tmp, free);
	}
}

char	**add_line_end(char **tabb, char *str)
{
	int	i;
	int	j;
	char	**new_tab;

	i = 0;
	if (tabb[0])
	{
		while (tabb[i])
			i++;
	}
	else
		i = 0;
	new_tab = malloc((i + 2) * sizeof(char *));
	if (!new_tab)
		return (NULL);
	j = 0; 
	while (j < i)
	{
		new_tab[j] = ft_substr(tabb[j], 0, ft_strlen(tabb[j]));
		j++;
	}
	new_tab[j++] = ft_substr(str, 0, ft_strlen(str));
	new_tab[j] = NULL;
	free_table(tabb);
	return (new_tab);

}

void	print_table(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			printf("%s\n", str[i++]);
	}
}
