/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:56:21 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/14 16:32:30 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_double_key(t_env *new_list, t_env *new_env)
{
	while (new_list)
	{
		if (!ft_strcmp(new_list->key, new_env->key))
			return (1);
		new_list = new_list->next;
	}
	return (0);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

void	insert(t_env **root, t_env *item)
{
	t_env	*temp;
	t_env	*ptr;

	temp = malloc(sizeof(t_env));
	temp -> val = item -> val;
	temp -> key = item -> key;
	temp -> content = item -> content;
	temp -> next = NULL;
	if (*root == NULL)
		*root = temp;
	else
	{
		ptr = *root;
		while (ptr-> next != NULL)
			ptr = ptr->next;
		ptr -> next = temp;
	}
}

void	ft_print_export(t_env *export_list)
{
	while (export_list)
	{
		if (!ft_strchr(export_list->content, '='))
			printf("declare -x %s\n", export_list->key);
		else
			printf("declare -x %s=\"%s\"\n", export_list->key, export_list->val);
		export_list = export_list->next;
	}
}

void	change_the_value(t_env **env_list, t_env *new_env)
{	
	t_env	*save;

	save = *env_list;
	while ((*env_list))
	{
		if (!ft_strcmp((*env_list)->key, new_env->key)
			&& new_env->c == '=')
		{
			if (new_env->plus == '+')
				ft_strcat((*env_list)->val, new_env->val);
			else
			{
				(*env_list)->val = new_env->val;
				(*env_list)->content = new_env->content;
			}
			break ;
		}
		(*env_list) = (*env_list)->next;
	}
	env_list = &save;
}

void	ft_export(t_list *head, t_env *env_list)
{
	t_env	*min;
	int		i;
	t_env	*new_env;
	t_env	*new_env_list;
	t_env	*export_list;
	t_env	*ins;

	i = 1;
	ins = env_list;
	new_env_list = NULL;
	export_list = NULL;
	if (head->cmd[1])
	{
		while (head->cmd[i])
		{
			new_env = ft_lstnew_env(head->cmd[i]);
			if (!check_double_key(env_list, new_env))
				add_node_to_list(&env_list, new_env);
			else
				change_the_value(&env_list, new_env);
			i++;
		}
	}
	while (ins)
	{
		insert(&new_env_list, ins);
		ins = ins -> next;
	}
	while (1)
	{
		if (new_env_list == NULL)
			break ;
		min = find_small(new_env_list);
		insert(&export_list, min);
		remove_node(&new_env_list, min->content);
	}
	if (!head->cmd[1])
		ft_print_export(export_list);
}
