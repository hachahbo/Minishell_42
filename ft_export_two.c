/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:38:31 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/14 15:50:15 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_small(t_env *list)
{
	t_env	*min;

	min = list;
	while (list->next)
	{
		if (ft_strcmp(min->content, list->next->content) > 0)
		min = list->next;
		list = list->next;
	}
	return (min);
}

void	remove_node(t_env **head, char *min)
{
	t_env	*current;
	t_env	*previous;

	previous = NULL;
	current = *head;
	while (current != NULL)
	{
		if (!ft_strcmp(current->content, min))
		{
			if (previous == NULL)
				*head = current->next;
			else
				previous->next = current->next;
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	add_node_to_list(t_env **head, t_env *new)
{
	t_env	*current;

	current = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	if (ft_strcmp(new->content, (*head)->content) < 0)
	{
		new->next = *head;
		*head = new;
		return ;
	}
	while (current->next != NULL
		&& ft_strcmp(current->next->content, new->content) < 0)
		current = current->next;
	new->next = current->next;
	current->next = new;
}

char	*until_equal_or_plus(char *big_str, char c)
{
	char	*str;
	int		i;

	i = 0;
	while (big_str[i] != c && big_str[i])
		i++;
	str = malloc(sizeof(char) * i + 1);
	i = 0;
	while (big_str[i] != c && big_str[i])
	{
		str[i] = big_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
