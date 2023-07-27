/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 20:13:17 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/27 13:51:30 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	 remove_node_2(t_env **head, char *min)
{
	t_env	*current;
	t_env	*previous;
	t_env	*env_tmp;

	previous = NULL;
	env_tmp = *head;
	current = *head;
	while (current != NULL)
	{
		if (!ft_strcmp(current->key, min))
		{
			if (previous == NULL)
				*head = current->next;
			else
				previous->next = current->next;
			free(current->val);
			free(current->key);
			free(current->content);
			free_double(current->env);
			free(current->hide_path);
			free(current);
			break;
		}
		previous = current;
		current = current->next;
	}
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

void	ft_unset(t_list *list, t_env **env_list, t_var *var)
{
	int	i;
	t_env *new_env;

	i = 1;
	(void)var;
	while (list->cmd[i])
	{
		new_env = ft_lstnew_env(list->cmd[i], NULL);
		if (check_is_valid(new_env, var))
			remove_node_2(env_list, list->cmd[i]);
		free(new_env->key);
		free(new_env->content);
		free(new_env->val);
		free(new_env->hide_path);
		free_double(new_env->env);
		free(new_env);
		i++;
	}
}

int	ft_check_after_exit(t_list *head)
{
	int	i;

	i = 1;
	while(head->cmd[i])
	{
		if(i > 1)
		{
			printf("bash: exit: too many arguments\n");
			return(0);
		}
		i++;
	}
	i = 1;
	while(head->cmd[1][i])
	{
		if(!ft_isdigit(head->cmd[1][i]))
		{
			printf("bash: exit: %s: numeric argument required", head->cmd[1]);
			return (0);
		}
		i++;
	}
	return (1);
}
int	ft_builtins(t_list *list, t_env **env_list, t_var *var)
{
	unsigned char x;

	x = 0;
	if (!ft_strcmp(list->cmd[0], "cd") || !ft_strcmp(list->cmd[0], "rm")
		|| !ft_strcmp(list->cmd[0], "/usr/bin/cd"))
		rendering_cd(list, env_list);
	else if (!ft_strcmp(list->cmd[0], "pwd") || !ft_strcmp(list->cmd[0], "/bin/pwd"))
		ft_pwd(*env_list, var);
	else if (!ft_strcmp(list->cmd[0], "echo") || !ft_strcmp(list->cmd[0], "/bin/echo"))
		ft_echo(list, var);
	else if (!ft_strcmp(list->cmd[0], "env") || !ft_strcmp(list->cmd[0], "/usr/bin/env"))
		ft_env(*env_list, var);
	else if (!ft_strcmp(list->cmd[0], "unset"))
		ft_unset(list, env_list, var);
	else if (!ft_strcmp(list->cmd[0], "export"))
		ft_export(list, env_list, var);
	else if (!ft_strcmp(list->cmd[0], "exit"))
	{
		printf("exit\n");
		if(list->cmd[1])
		{
			if(ft_check_after_exit(list))
				x = ft_atoi(list->cmd[1]);
		}
		exit(x);
	}
	else
		return (1);
	state_exit = 0;
	return (0);
}
