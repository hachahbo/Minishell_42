/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:25:26 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/03 17:09:01 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lexer(t_list *node)
{
	char *str;

	str = node->content; 
	if(strcmp(str, " ") == 0)
		node->type = WHITE_SPACE;
	else if(strcmp(str, "\n")== 0)
		node->type = NEW_LINE;
	else if(strcmp(str, "\'")== 0)
		node->type = QOUTE;
	else if(strcmp(str, "\"")== 0)
		node->type = DOUBLE_QUOTE;
	else if(strcmp(str, "\\")== 0)
		node->type = ESCAPE;
	else if(strcmp(str, "$") == 0)
		node->type = ENV;
	else if(strcmp(str, "|")== 0)
		node->type = PIPE_LINE;
	else if(strcmp(str, "<")== 0)
		node->type = REDIR_IN;
	else if(strcmp(str, ">") == 0)
		node->type = REDIR_OUT;
	else if(strcmp(str, "<<") == 0)
		node->type  = HERE_DOC;
	else if(strcmp(str, ">>") == 0)
		node ->type = DREDIR_OUT;
	else 
		node->type = WORD; 
	return (0);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (!tmp)
		return (0);
	tmp->content = ft_strdup(content);
	ft_lexer(tmp);
	tmp->next = 0;
	return (tmp);
}
