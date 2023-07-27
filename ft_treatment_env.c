/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treatment_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:03:10 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/27 23:03:59 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_env(char *str, char **env)
{
	t_env	*tmp;
	char	*key;
	char	*val;

	tmp = (t_env *)malloc(sizeof(t_env));
	if (!tmp)
		affiche_error();
	if (!str)
		return (tmp->key = ft_strdup("000"), tmp);
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
	{
		val = delete_back_slash(val);
		tmp->c = val[0];
	}
	tmp->hide_path = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	tmp->content = ft_strdup(str);
	tmp->key = key;
	tmp->env = ft_str_double_dup(env);
	if (val == 0)
		tmp->val = ft_strdup(NULL);
	else
		tmp->val = ft_strdup(val + 1);
	tmp->next = 0;
	free(val);
	return (tmp);
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
