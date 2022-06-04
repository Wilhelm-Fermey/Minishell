/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 09:53:43 by zkansoun          #+#    #+#             */
/*   Updated: 2022/03/17 09:59:52 by zkansoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*prev;
	t_list	*temp;

	temp = *lst;
	while (temp != NULL)
	{
		prev = temp;
		temp = temp->next;
		ft_lstdelone(prev, del);
	}
	*lst = NULL;
}
