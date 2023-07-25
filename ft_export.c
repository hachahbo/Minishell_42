/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:15:35 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/25 14:43:17 by amoukhle         ###   ########.fr       */
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

char	*until_equal_or_plus(char *big_str, char c)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if(!ft_strchr(big_str, '='))
		return (ft_strdup(big_str));
	while (big_str[i] != c && big_str[i])
		i++;
	str = malloc(sizeof(char) * i + 1);
	i = 0;
	j = 0;
	while (big_str[i] != c && big_str[j])
	{
		if (big_str[j] == '\\')
			j++;
		str[i] = big_str[j];
		i++;
		j++;
	}
	if (ft_strchr(big_str, '\\'))
		i--;
	str[i] = '\0';
	return (str);
}

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

void	ft_print_export(t_env *export_list, t_var *var)
{
	if (!ft_strcmp(export_list->key, "000"))
		export_list = export_list->next;
	if (!export_list)
		return ;
	while (export_list)
	{	
		if (!ft_strchr(export_list->content, '='))
		{
			write(var->std_out, "declare -x ", 11);
			write(var->std_out, export_list->key, ft_strlen(export_list->key));
			write(var->std_out, "\n", 1);
		}
		else
		{
			write(var->std_out, "declare -x ", 11);
			write(var->std_out, export_list->key, ft_strlen(export_list->key));
			write(var->std_out, "=\"", 2);
			write(var->std_out, export_list->val, ft_strlen(export_list->val));
			write(var->std_out, "\"\n", 2);
		}
		export_list = export_list->next;
	}
}

void	change_the_value(t_env **env_list, t_env *new_env)
{	
	t_env	*save;
	char	*str =NULL;

	save = *env_list;
	while (save)
	{
		if (!ft_strcmp(save->key, new_env->key) && new_env->c == '=')
		{
			if (new_env->plus == '+')
			{
				str = save->val;
				save->val = ft_strjoin(save->val, new_env->val);
				free(str);
				free(new_env->val);
				free(new_env->key);
				free(new_env->hide_path);
				free_double(new_env->env);
				free(new_env->content);
			}
			else
			{
				str = save->val;
				save->val = new_env->val;
				free(str);
				save->c = '=';
				str = save->content;
				save->content = new_env->content;
				free(str);
				free(new_env->key);
				free_double(new_env->env);
				free(new_env->hide_path);
			}
			break ;
		}
		save = save->next;
	}
	if(new_env->c != '=')
	{
		free(str);
		free(new_env->val);
		free(new_env->key);
		free(new_env->content);
		free_double(new_env->env);
		free(new_env->hide_path);
	}
	free(new_env);
}

void ft_print_error(char *s , t_env *new_env, char *str, t_var *var)
{
	write(var->std_out, "export : `", 10);
	write(var->std_out, s, ft_strlen(s));
	write(var->std_out, "\': not a valid identifier\n", 26);
	free(str);
	free(new_env->key);
	free(new_env->content);
	free(new_env->val);
	free(new_env->hide_path);
	free_double(new_env->env);
	free(new_env);
}

int	check_is_valid(t_env *new_env, t_var *var)
{
	int		i;
	char	*str =NULL;

	if (!(ft_isalpha(new_env->key[0]) || new_env->key[0] == '_'))
		return (ft_print_error(new_env->key, new_env, str, var), 0);
	i = 1;
	while (new_env->key[i])
	{
		if (!ft_isalpha(new_env->key[i])
			&& !ft_isdigit(new_env->key[i]) && !(new_env->key[i] == '_'))
			return (ft_print_error(new_env->key, new_env, str, var), 0);
		i++;
	}
	i = ft_strlen(new_env->content);
	if (new_env->content[i - 1] == '+' && !new_env->content[i])		
		return (ft_print_error(new_env->content, new_env, str, var), 0);
	i = 0;
	str = until_equal_or_plus(new_env->content, '=');
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '+')
			return (ft_print_error(new_env->content, new_env, str, var), 0);
		i++;
	}
	return (free(str), 1);
}

int	add_or_change(t_env **env_list, t_list *head, char **env, t_var *var)
{
	t_env	*new_env;
	int		i;

	i = 1;
	while (head->cmd[i])
	{
		new_env = ft_lstnew_env(head->cmd[i], env);
		if (!new_env)
			return (0);
		if (!check_double_key(*env_list, new_env))
		{
			if (!check_is_valid(new_env, var))
				return (0);
			ft_lstadd_back_env(env_list, new_env);
		}
		else
			change_the_value(env_list, new_env);
		i++;
	}
	return (1);
}

void ft_free(t_env *head)
{
	while(head)
	{
		free(head);
		head = head->next;
	}
	free(head);
}

void	ft_only_export(t_list *head, t_env *export_list, t_var *var)
{
	if (!head->cmd[1])
		ft_print_export(export_list, var);
	ft_free(export_list);
}

int	ft_export(t_list *head, t_env **env_list, t_var *var)
{
	t_env	*help;
	t_env	*new_env_list;
	t_env	*export_list;

	help = *env_list;
	new_env_list = NULL;
	export_list = NULL;
	if (head->cmd[1])
		if (!add_or_change(env_list, head, (*env_list)->env, var))
			return (0);
	while (help)
	{
		insert(&new_env_list, help);
		help = help -> next;
	}
	while (1)
	{
		if (new_env_list == NULL)
			break ;
		help = find_small(new_env_list);
		insert(&export_list, help);
		remove_node(&new_env_list, help->content);
	}
	ft_only_export(head, export_list, var);
	return (1);
}