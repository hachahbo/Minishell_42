/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_infile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:29:40 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/21 18:54:47 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_msg_null_DOC(t_list *node)
{
	write(2, "bash: ", 6);
	write(2, node->cmd[1], ft_strlen(node->cmd[1]));
	write(2, ": ambiguous redirect\n", 21);
	exit(1);
}

void	ft_msg_error_infile(char *str_DOC)
{
	int	len_error;

	len_error = ft_strlen(strerror(errno));
	write(2, "bash: ", 6);
	write(2, str_DOC, ft_strlen(str_DOC));
	write (2, ": ", 2);
	write(2, strerror(errno), len_error);
	write (2, "\n", 1);
	exit(1);
}

int	ft_open_infile(t_list *node, t_var *var, t_env *env_list)
{
	t_list		*list;
	char		*str_DOC;
	t_list_str	*list_str;
	int			infile;
	
	list = NULL;
	list_str = NULL;
	ft_init_var(var);
	ft_make_list(node->cmd[1], &list, var);
	str_DOC = get_string_DOC(list, var, env_list, &list_str);
	if (!str_DOC)
		ft_msg_null_DOC(node);
	infile = open(str_DOC, O_RDONLY, 0777);
	if (infile == -1)
		ft_msg_error_infile(str_DOC);
	ft_lstclear(&list);
	list_strclear(&list_str);
	return (infile);
}
