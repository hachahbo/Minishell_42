/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 06:09:13 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/08 11:44:27 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_env_list(char **env, t_list **env_list)
{
	int		i;
	t_list	*new;

	i = 0;
	while(env[i])
	{
		new = ft_lstnew(env[i]);
		ft_lstadd_back(env_list, new);
		i++;
	}
}

void 	ft_make_list(char *input, t_list **head)
{
	int flag1;
	int flag2;
	t_list *new;
	char  *str;
	int start;
	int end;
	
	start = 0;
	end = 0;
	flag1 = 0;
	flag2 = 0;
	while (1)
	{
		input = skip_spaces(input);
		str = check_data(input, &start, &end);
		if(str == NULL)
		{
			free(str);
			break ;
		}
		new = ft_lstnew(str);
		ft_status(new, &flag1, &flag2);
		ft_lstadd_back(head, new);
		free(str);
	}
}

int	serche_for_DOC(t_list *list)
{
	if (list->type == WORD)
		list = list->prev;
	if (list->type == ENV)
		list = list->prev;
	while (list && (list->type == DOUBLE_QUOTE || list->type == QOUTE))
		list = list->prev;
	while (list && list->type == WHITE_SPACE)
		list = list->prev;
	if (list && (list->type == HERE_DOC || list->type == DREDIR_OUT
		|| list->type == REDIR_IN || list->type == REDIR_OUT) && list->state == GENERAL)
		return (0);
	return (1);
}

char *handle_env(t_list *list, t_list *env_list, int *num_env)
{
	if (list->type == ENV && list->state == GENERAL
		&& (list->next == NULL || list->next->type == WHITE_SPACE))
		return (list->content);
	else if (list->type == ENV && list->state == GENERAL
		&& (list->next->type == QOUTE || list->next->type == DOUBLE_QUOTE))
		return ("");
	else if (list->type == ENV && list->state == IN_QUOTE)
		return (list->content);
	else if (list->type == ENV && list->state == IN_DQUOTE)
	{
		if (list->next->type == WORD && *num_env % 2 != 0)
		{
			if (serche_for_DOC(list) == 1)
				return (ft_expand_value(list->next->content, env_list));
			else
				return (list->content);
		}
		else
			return (list->content);
	}
	else if (list->type == ENV && list->state == GENERAL
		&& list->next->type == WORD && *num_env % 2 != 0)
	{
		if (serche_for_DOC(list) == 1)
			return (ft_expand_value(list->next->content, env_list));
		else
			return (list->content);
	}
	return (list->content);
}

void	ft_make_new_list(t_list *head, t_list **new_list, t_list *env_list)
{
	char	*str;
	t_list	*new;
	char	*tmp;
	int		in_join;
	int		num_env;

	num_env = 0;
	while (head)
	{
		in_join = 0;
		str = NULL;
		if (head->type != WORD && head->type != QOUTE
			&& head->type != DOUBLE_QUOTE && head->type != ENV)
			str = head->content;
		while (head && (head->type == WORD || head->type == ENV
			|| head->type == QOUTE || head->type == DOUBLE_QUOTE
			|| head->state == IN_QUOTE || head->state == IN_DQUOTE))
		{
			if ((head->type == QOUTE && head->state == GENERAL)
				|| (head->type == DOUBLE_QUOTE && head->state == GENERAL)
				|| (head->type == WORD && head->prev && head->prev->type == ENV
				&& head->state != IN_QUOTE && num_env % 2 != 0 && serche_for_DOC(head) == 1))
			{
				head = head->next;
				continue;
			}
			if (head->type == ENV)
			{
				num_env++;
				tmp = handle_env(head, env_list, &num_env);
				if (!tmp)
				{
					head = head->next;
					continue;
				}
				str = ft_strjoin(str, tmp);
			}
			else
				str = ft_strjoin(str, head->content);
			head = head->next;
			in_join = 1;
		}
		if (str)
		{
			new = ft_lstnew(str);
			if (in_join == 0)
				new->state = GENERAL;
			else
				new->state = IN_DQUOTE;
			ft_lstadd_back(new_list, new);
		}
		if (in_join == 0 && head)
			head = head->next;
		num_env = 0;
	}
}

char *ft_expand_value(char *str, t_list *env_list)
{
	char	*value;

	value = NULL;
	while (env_list)
	{
		if (ft_strncmp(str, env_list->content, ft_strlen(str)) == 0 && env_list->content[ft_strlen(str)] == '=')
			value = &env_list->content[ft_strlen(str) + 1];
		env_list = env_list->next;
	}
	return (value);
}

void	ft_make_new_list_w_s(t_list *new_list, t_list **new_list_w_s)
{
	t_list *new;

	while (new_list)
	{
		if (new_list->type == WHITE_SPACE && new_list->state == GENERAL)
		{
			new_list = new_list->next;
			continue;
		}
		new = ft_lstnew(new_list->content);
		ft_lstadd_back(new_list_w_s, new);
		new_list = new_list->next;
	}
}
