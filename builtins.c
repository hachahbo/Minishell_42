/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 20:13:17 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/24 01:16:15 by amoukhle         ###   ########.fr       */
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
	while (list->cmd[i])
	{
		remove_node_2(&env_list, list->cmd[i]);
		i++;
	}
}

int	ft_builtins(t_list *list, t_env *env_list, t_var *var)
{
	(void)env_list;
	(void)var;
	if (!ft_strcmp(list->cmd[0], "cd") || !ft_strcmp(list->cmd[0], "/usr/bin/cd"))
		rendering_cd(list, env_list);
	else if (!ft_strcmp(list->cmd[0], "pwd") || !ft_strcmp(list->cmd[0], "/bin/pwd"))
		ft_pwd(env_list, var);
	else if (!ft_strcmp(list->cmd[0], "echo") || !ft_strcmp(list->cmd[0], "/bin/echo"))
		ft_echo(list, var);
	else if (!ft_strcmp(list->cmd[0], "env") || !ft_strcmp(list->cmd[0], "/usr/bin/env"))
		ft_env(env_list, var);
	else if (!ft_strcmp(list->cmd[0], "unset"))
		ft_unset(list, env_list);
	else if (!ft_strcmp(list->cmd[0], "export"))
		ft_export(list, env_list, var);
	else if (!ft_strcmp(list->cmd[0], "exit"))
	{
		printf("exit\n");
		exit(0);
	}
	else
		return (1);
	state_exit = 0;
	return (0);
}
