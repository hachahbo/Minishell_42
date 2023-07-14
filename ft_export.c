/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:56:21 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/14 15:03:16 by hachahbo         ###   ########.fr       */
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

t_env	*ft_lstlast_env(t_env *lst)
{
	t_env	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	while (tmp->next != 0)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;
	int		i;

	i = 0;
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast_env(*lst);
	tmp->next = new;
}

int	check_the_plus(char *str)
{
    int	i;

    i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i+1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

t_env	*ft_lstnew_env(char *str)
{
	t_env	*tmp;
	char	*key;
	char	*val;

	tmp = (t_env *)malloc(sizeof(t_env));
	if (!tmp)
		return (0);
	key = until_equal_or_plus(str, '=');
	tmp->plus = 0;
	if (check_the_plus(key))
	{
		tmp->plus = '+';
		free(key);
		key = until_equal_or_plus(str, '+');
	}
	val = ft_strchr(str, '=');
	if (val)
		tmp->c = val[0];
	tmp->content = ft_strdup(str);
	tmp->key = ft_strdup(key);
	if (val == 0)
		tmp->val = ft_strdup(NULL);
	else
		tmp->val = ft_strdup(val + 1);
	tmp->next = 0;
	return (tmp);
}

int	check_double_nodes(t_list *new, t_list **env_list)
{
    char	*str;
    char	*str2;
    char	*save;
    t_list	*head;

	head = *env_list;
	str = until_equal_or_plus(new->content, '=');
	while(*env_list)
	{
		str2 = until_equal_or_plus((*env_list)->content, '=');
		if(!ft_strcmp(str, str2))
		{ 
			save = ft_strchr(new->content, '=');
			if(!save)
				return (1);
			(*env_list)->content = new->content;
			return (1);
		}
		(*env_list) = (*env_list)->next;
	}
    
    env_list = &head;
    return (0);
}
void make_copy_env_list(t_list *env_list, t_env **new_env_list)
{
    t_env *new_env;
    
    while(env_list)
    {
        new_env = ft_lstnew_env(env_list->content);
        ft_lstadd_back_env(new_env_list, new_env);
        env_list = env_list->next;
    }
}
void duplicate_env(t_env *env_list, t_env **new_env_list)
{
    t_env *new_env;
    while((*new_env_list))
    {
        free((*new_env_list));
        (*new_env_list) = (*new_env_list) -> next;
    }
    while(env_list)
    {
        new_env = ft_lstnew_env(env_list->content);
        ft_lstadd_back_env(new_env_list, new_env);
        env_list = env_list->next;
    }
}
int check_double_key(t_env *new_list, t_env *new_env)
{
    while(new_list)
    {
        if(!ft_strcmp(new_list->key, new_env->key))
            return(1);
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
	{
		i++;
	}
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
void ft_export(t_list *head, t_env *env_list)
{
    t_env *min;
    int i;
    t_env *save;

    save = env_list;
    t_env *new_env;
    t_env *new_env_list = NULL;
    t_env *export_list = NULL;
	t_env *ins = env_list;
        
    i = 1;
    if(head->cmd[1])
    {
        while(head->cmd[i])
        {
            new_env = ft_lstnew_env(head->cmd[i]);
           if(!check_double_key(env_list, new_env) )
                add_node_to_list(&env_list, new_env);
            else
            {
                while(env_list)
                {
                    if(!ft_strcmp(env_list->key, new_env->key) && new_env->c == '=')
                    {
                        if(new_env->plus == '+')
                            ft_strcat(env_list->val, new_env->val);
                        else
                        {
                            env_list->val = new_env->val;
                            env_list->content = new_env->content;
                        }
                        break ;
                    }
                    env_list = env_list->next;
                }
                env_list = save;
            }
            i++;
        }
    }
    while(ins)
    {
        insert(&new_env_list,ins);
        ins = ins -> next;
    }
    while(1)
    {
        if(new_env_list == NULL)
            break;
        min = find_small(new_env_list);
        insert(&export_list, min);
        remove_node(&new_env_list, min->content);
    }
    if(!head->cmd[1])
    {
        while(export_list)
        {
            if(!ft_strchr(export_list->content, '='))
                printf("declare -x %s\n", export_list->key);
            else       
                printf("declare -x %s=\"%s\"\n", export_list->key, export_list->val);
           export_list= export_list->next;
        }
    }
}
