/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_infile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:29:40 by amoukhle          #+#    #+#             */
/*   Updated: 2023/06/20 17:29:29 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_env_DOC(t_list *list, t_list *env_list, int num_env)
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
		if (list->next->type == WORD && num_env % 2 != 0)
				return (ft_expand_value(list->next->content, env_list));
		else if (list->next->type == Q_MARK && num_env % 2 != 0)
				return (ft_itoa(state_exit));
	}
	return (list->content);
}

void	ft_init_var(t_var *var)
{
	var->start = 0;
	var->end = 0;
	var->flag1 = 0;
	var->flag2 = 0;
	var->num_env = 0;
	var->str = NULL;
}

int	skip_node_DOC(t_list *list, t_var *var)
{
	if ((list->type == QOUTE && list->state == GENERAL)
		|| (list->type == DOUBLE_QUOTE && list->state == GENERAL)
		|| ((list->type == WORD || list->type == Q_MARK) && list->prev && list->prev->type == ENV
		&& list->state != IN_QUOTE && var->num_env % 2 != 0))
		return (0);
	return (1);
}

void	ft_skip_node_DOC(t_list *list, t_var *var)
{
	if (!var->str && (list->type == DOUBLE_QUOTE || list->type == QOUTE))
		var->str = "";
	var->num_env = 0;
	var->skip = 1;
}

char	*get_string_DOC(t_list *list, t_var *var, t_list *env_list, t_list_str *list_str)
{
	char	*tmp;

	while (list)
	{
		var->skip = 0;
		if (!skip_node_DOC(list, var))
			ft_skip_node_DOC(list, var);
		if (!var->skip && list->type == ENV)
		{
			var->num_env++;
			tmp = handle_env_DOC(list, env_list, var->num_env);
			if (!tmp || (list->state == GENERAL && ft_strcmp(tmp, "$") && ft_strchr(tmp, ' ')))
				var->skip = 1;
			if (!var->skip)
				var->str = join_list_str(var->str, tmp, &list_str);
		}
		else if (!var->skip)
			var->str = join_list_str(var->str, list->content, &list_str);
		list = list->next;
	}
	return (var->str);
}

int	ft_open_infile(t_list *node, t_var *var, t_list *env_list)
{
	t_list		*list;
	char		*str_DOC;
	t_list_str	*list_str;
	
	list = NULL;
	list_str = NULL;
	ft_init_var(var);
	ft_make_list(node->cmd[1], &list, var);
	str_DOC = get_string_DOC(list, var, env_list, list_str);
	// printf("str: [%s]\n", str_DOC);
	return (0);
}
