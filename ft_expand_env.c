/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:03:57 by amoukhle          #+#    #+#             */
/*   Updated: 2023/06/19 23:06:55 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_value_of_env(char *str, char *tmp, t_list_str **list_str, t_list **new_list)
{
	int		i;
	char	**str_split;

	str_split = ft_split(tmp, ' ');
	i = 0;
	while(str_split[i + 1])
	{
		str = ft_strjoin(str, str_split[i]);
		list_stradd_back(list_str, new_list_str(str));
		i++;
		ft_lstadd_back(new_list, ft_lstnew(str, NULL));
		str = NULL;
	}
	str = ft_strjoin(str, str_split[i]);
	list_stradd_back(list_str, new_list_str(str));
	free_double(str_split);
	return (str);
}

char *handle_env(t_list *list, t_list *env_list, int num_env)
{
	if ((list->type == ENV && list->state == GENERAL
		&& (list->next == NULL || list->next->type == WHITE_SPACE))
		|| (list->type == ENV && list->state == IN_QUOTE))
		return (list->content);
	else if (list->type == ENV && list->state == GENERAL && num_env % 2 != 0
		&& (list->next->type == QOUTE || list->next->type == DOUBLE_QUOTE))
		return ("");
	else if (list->type == ENV && (list->state == IN_DQUOTE || list->state == GENERAL))
	{
		if (list->next->type == WORD && num_env % 2 != 0 && serche_for_DOC(list) == 1)
				return (ft_expand_value(list->next->content, env_list));
		else if (list->next->type == Q_MARK && num_env % 2 != 0 && serche_for_DOC(list) == 1)
				return (ft_itoa(state_exit));
	}
	return (list->content);
}
void	make_env_list(char **env, t_list **env_list)
{
	int		i;
	t_list	*new;

	i = 0;
	while(env[i])
	{
		new = ft_lstnew(env[i], NULL);
		ft_lstadd_back(env_list, new);
		i++;
	}
}
char *ft_expand_value(char *str, t_list *env_list)
{
	char	*value;

	value = NULL;
	while (env_list)
	{
		if (ft_strncmp(str, env_list->content, ft_strlen(str)) == 0
			&& env_list->content[ft_strlen(str)] == '=')
			value = &env_list->content[ft_strlen(str) + 1];
		env_list = env_list->next;
	}
	return (value);
}