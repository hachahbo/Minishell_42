/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 06:49:49 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/01 14:04:08 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_strcmp(char *s1, char *s2)
{
	int i;
	i = 0;
	while(s1[i] && s2[i] && s1[i] == s2 [i])
		i++;
	return(s1[i] - s2[i]);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;
	t_list	*freed;

	temp = *lst;
	while (temp != NULL)
	{
		freed = temp;
		temp = temp->next;
		free(freed->content);
		free(freed);
	}
	*lst = NULL;
}

void printlist(t_list *head)
{
	printf("command			state			token\n");
	while(head)
	{
		printf("%s			%d			%d\n", head->content, head->state, head->type);
		head= head->next;
	}
	printf("\n");
}

int ft_empty(t_list *head)
{
	int i;

	i = 0;
	while(head->next)
	{
		head = head->next;
	}
	if(is_spaces(head->content) && !head->next)
		return (1);
	return (0);
}