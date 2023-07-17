/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:25:45 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/17 09:13:03 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *path)
{
	chdir(path);
}

int	ft_check_args_of_cd(t_list *head)
{
	if (!head->cmd[1] || !ft_strcmp(head->cmd[1], "~"))
		ft_cd("/Users/hachahbo");
	else if (!ft_strcmp(head->cmd[1], ".."))
		ft_cd("..");
	else if (!ft_strcmp(head->cmd[1], "."))
		ft_cd(".");
	else if (!ft_strcmp(head->cmd[1], "/"))
		ft_cd("/");
	else
		ft_cd(head->cmd[1]);
	return (0);
}

int	rendering_cd(t_list *list)
{
	if (list == NULL)
		return (0);
	print_double_list(list);
	ft_check_args_of_cd(list);
	return (0);
}
