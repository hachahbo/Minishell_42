/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 20:13:17 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/23 00:14:11 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_node_2(t_env **head, char *min)
{
	t_env	*current;
	t_env	*previous;

	previous = NULL;
	current = *head;
	while (current != NULL)
	{
		if (!ft_strcmp(current->key, min))
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

void	ft_unset(t_list *list, t_env *env_list)
{
	int	i;

	i = 1;
	// printf("hamza\n");
	while (list->cmd[i])
	{
		remove_node_2(&env_list, list->cmd[i]);
		i++;
	}
}

int	 ft_builtins(t_list *list, t_env *env_list, int flag)
{
	(void)env_list;
	if (!ft_strcmp(list->cmd[0], "cd"))
		rendering_cd(list, env_list);
	else if (!ft_strcmp(list->cmd[0], "pwd"))
		ft_pwd(env_list);
	else if (!ft_strcmp(list->cmd[0], "echo"))
		ft_echo(list,  flag);
	else if (!ft_strcmp(list->cmd[0], "env"))
		ft_env(env_list);
	else if (!ft_strcmp(list->cmd[0], "unset"))
		ft_unset(list, env_list);
	else if (!ft_strcmp(list->cmd[0], "export"))
		ft_export(list, env_list);
	else if (!ft_strcmp(list->cmd[0], "exit"))
	{
		printf("exit\n");
		exit(1);
	}
	else
		return (1);
	return (0);
}