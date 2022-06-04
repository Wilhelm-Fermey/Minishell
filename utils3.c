/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilhelmfermey <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:38:29 by wilhelmfermey     #+#    #+#             */
/*   Updated: 2022/05/31 13:50:33 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	update_exit_code(char *str)
{
	t_list	*tmp;

	tmp = *g_envp;
	((char *)(tmp->content))[0] = 0;
	((char *)(tmp->content))[1] = 0;
	((char *)(tmp->content))[2] = 0;
	free(tmp->content);
	tmp->content = ft_strjoin("?=", str);
}

void	add_list(t_seg **seg)
{
	t_seg	*temp;
	t_seg	*new;

	temp = *seg;
	while (temp->next != NULL)
		temp = temp->next;
	new = malloc(sizeof(t_seg));
	if (!new)
		printf("error malloc\n");
	new->next = NULL;
	temp->next = new;
}
