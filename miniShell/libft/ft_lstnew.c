/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:14:46 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/03/16 18:16:27 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content, int index)
{
	t_list	*new;

	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->index = index;
	new->next = NULL;
	return (new);
}

void	printll(t_list *chaine)
{
	while (chaine != NULL)
	{
		ft_printf("[%d] --> %s\n ", chaine->index, (chaine->content));
		chaine = chaine->next;
	}
}

/*
#include <stdio.h>
int main(void)
{
	int *v;
	//v = &c;
	t_list *t = ft_lstnew ((void *)"c");
	//int c=7;

	//t = ft_lstnew (v);
	printf("%s \n %p", (t->content), t->next);
	free(t);
	
}*/