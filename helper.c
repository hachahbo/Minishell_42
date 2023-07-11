/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 06:49:49 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/10 18:38:07 by hachahbo         ###   ########.fr       */
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

void list_strclear(t_list_str **lst)
{
	t_list_str	*temp;
	t_list_str	*freed;

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

void	ft_lstclear_env(t_env **lst)
{
	t_env	*temp;
	t_env	*freed;

	temp = *lst;
	while (temp != NULL)
	{
		freed = temp;
		temp = temp->next;
		if (freed->content)
			free(freed->content);
		free(freed);
	}
	*lst = NULL;
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
		if (freed->content)
			free(freed->content);
		free_double(freed->cmd);
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

void print_double_list(t_list *head)
{
	int	i;

	i = 1;
	while(head)
	{
		printf("cmd: [%s]\n",head->cmd[0]);
		i = 1;
		while (head->cmd[i])
		{
			printf("args: \"%s\"   ||   ",head->cmd[i]);
			i++;
		}
		i = 0;
		printf("\n");
		head = head->next;
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