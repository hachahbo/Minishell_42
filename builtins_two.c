/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 09:54:25 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/30 13:51:13 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_here(t_env *current)
{
	free(current->val);
	free(current->key);
	free(current->content);
	free_double(current->env);
	free(current->hide_path);
	free(current);
}

void	hide_path(t_env **head, char *min)
{
	t_env	*env_tmp;

	env_tmp = *head;
	if (!ft_strcmp("PATH", min))
	{
		while (env_tmp)
		{
			free(env_tmp->hide_path);
			env_tmp->hide_path = NULL;
			env_tmp = env_tmp->next;
		}
	}
}

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
			free_here(current);
			break ;
		}
		previous = current;
		current = current->next;
		hide_path(head, min);
	}
}

void	ft_unset(t_list *list, t_env **env_list, t_var *var)
{
	int		i;
	t_env	*new_env;

	i = 1;
	while (list->cmd[i])
	{
		new_env = ft_lstnew_env(list->cmd[i], NULL);
		if (check_is_valid(new_env, var))
		{
			remove_node_2(env_list, list->cmd[i]);
			free_double(new_env->env);
			free(new_env->key);
			free(new_env->content);
			free(new_env->val);
			free(new_env->hide_path);
			free(new_env);
		}
		i++;
	}
}
