/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:27:30 by amoukhle          #+#    #+#             */
/*   Updated: 2023/06/22 15:56:43 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_file(char *delimiter, int fd, t_var *var)
{
	char	*line;
	t_list_str	*list_str;

	list_str = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (!var->q_dq)
			ft_expand_in_heredoc(var, line, &list_str, fd);
		else
			write(fd, line, ft_strlen(line));
		free(line);
		list_strclear(&list_str);
	}
	close (fd);
}

void	ft_expand_in_heredoc(t_var *var, char *line, t_list_str **list_str, int fd)
{
	t_list	*list;
	char	*str;

	list = NULL;
	ft_init_var_delimiter(var);
	ft_make_list(line, &list, var);
	str = get_string_delimiter(list, var, var->env_list, list_str);
	ft_lstclear(&list);
	write(fd, str, ft_strlen(str));
}

char	*get_string_delimiter(t_list *list, t_var *var, t_list *env_list, t_list_str **list_str)
{
	char	*tmp;

	while (list)
	{
		var->skip = 0;
		if (!skip_node_delimiter(list, var))
			ft_skip_node_delimiter(var);
		if (!var->skip && list->type == ENV)
		{
			var->num_env++;
			tmp = handle_env_in_heredoc(list, env_list, var->num_env);
			if (!tmp)
				tmp = "";
			var->str = join_list_str(var->str, tmp, list_str);
		}
		else if (!var->skip)
			var->str = join_list_str(var->str, list->content, list_str);
		list = list->next;
	}
	return (var->str);
}

void	ft_init_var_delimiter(t_var *var)
{
	var->start = 0;
	var->end = 0;
	var->flag1 = 0;
	var->flag2 = 0;
	var->num_env = 0;
	var->str = NULL;
}

char	*handle_env_in_heredoc(t_list *list, t_list *env_list, int num_env)
{
	if ((list->type == ENV && list->state == GENERAL
		&& (list->next == NULL || list->next->type == WHITE_SPACE)))
		return (list->content);
	else if (list->type == ENV)
	{
		if (list->next->type == WORD && num_env % 2 != 0)
				return (ft_expand_value(list->next->content, env_list));
		else if (list->next->type == Q_MARK && num_env % 2 != 0)
				return (ft_itoa(state_exit));
	}
	return (list->content);
}
