/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 06:09:13 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/01 14:19:21 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_env_list(char **env, t_list **env_list)
{
	int		i;
	t_list	*new;

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

void	ft_make_new_list(t_list *head, t_list **new_list)
{
	char	*str;
	t_list	*new;
	int		start_word;
	int		is_word;

	start_word = 0;
	while (head)
	{
		is_word = 0;
		if (head)
		{
			str = head->content;
			if (head->type == WORD || head->type == QOUTE
				|| head->type == DOUBLE_QUOTE)
				is_word = 1;
			start_word = 1;
		}
		head = head->next;
		while (head && is_word == 1 && (head->type == QOUTE || head->state == IN_DQUOTE
			|| head->type == DOUBLE_QUOTE || head->type == WORD || head->state == IN_QUOTE))
		{
			str = ft_strjoin(str, head->content);
			head = head->next;
			start_word = 0;
		}
		new = ft_lstnew(str);
		ft_lstadd_back(new_list, new);
		if (start_word == 0)
			free(str);
		if (!head)
			break ;
	}
	
}