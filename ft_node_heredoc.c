/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:53:51 by amoukhle          #+#    #+#             */
/*   Updated: 2023/06/22 15:58:42 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_node_heredoc(t_list *list)
{
	if ((list->type == QOUTE && list->state == GENERAL)
		|| (list->type == DOUBLE_QUOTE && list->state == GENERAL))
		return (0);
	return (1);
}

void	ft_skip_node_heredoc(t_list *list, t_var *var)
{
	if (!var->str && (list->type == DOUBLE_QUOTE || list->type == QOUTE))
		var->str = "";
	var->num_env = 0;
	var->skip = 1;
	var->q_dq = 1;
}

int	skip_node_delimiter(t_list *list, t_var *var)
{
	if (((list->type == WORD || list->type == Q_MARK) && list->prev && list->prev->type == ENV
		&& var->num_env % 2 != 0))
		return (0);
	return (1);
}

void	ft_skip_node_delimiter(t_var *var)
{
	var->num_env = 0;
	var->skip = 1;
}
