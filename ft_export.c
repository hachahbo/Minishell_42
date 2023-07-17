/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:56:21 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/17 08:54:08 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!ft_strcmp(export_list->key, "000"))
		export_list = export_list->next;
	if (!export_list)
		return ;
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
				(*env_list)->c = '=';
				(*env_list)->content = new_env->content;
			}
			break ;
		}
		(*env_list) = (*env_list)->next;
	}
	env_list = &save;
}
// int first_check_the_value(t_env *new)
// {
// }
int	add_or_change(t_env *env_list, t_list *head)
{
	t_env	*new_env;
	int		i;

	i = 1;
	while (head->cmd[i])
	{
		new_env = ft_lstnew_env(head->cmd[i]);
		if (!new_env)
			return (0);
		if (!check_double_key(env_list, new_env))
		{
			if (!check_is_valid(new_env))
				return (0);
			ft_lstadd_back_env(&env_list, new_env);
		}
		else
		{
			// if(first_check_the_value(new_env))
			// 	return(0);
			change_the_value(&env_list, new_env);
		}
		i++;
	}
	return (1);
}

int	ft_export(t_list *head, t_env *env_list)
{
	t_env	*min;
	t_env	*new_env_list;
	t_env	*export_list;
	t_env	*ins;

	ins = env_list;
	new_env_list = NULL;
	export_list = NULL;
	if (head->cmd[1])
		if (!add_or_change(env_list, head))
			return (0);
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
	return (1);
}
