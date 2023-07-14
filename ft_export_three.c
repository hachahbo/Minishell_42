/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:44:03 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/14 15:51:05 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (str[i] == '+' && str[i + 1] == '\0')
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
	while (*env_list)
	{
		str2 = until_equal_or_plus((*env_list)->content, '=');
		if (!ft_strcmp(str, str2))
		{
			save = ft_strchr(new->content, '=');
			if (!save)
				return (1);
			(*env_list)->content = new->content;
			return (1);
		}
		(*env_list) = (*env_list)->next;
	}
	env_list = &head;
	return (0);
}