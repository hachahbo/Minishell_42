/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:25:45 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/14 10:29:49 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *path)
{
	chdir(path);
}
int ft_check_args_of_cd(t_list *head)
{
	char *new_path;
	
	head = head->next;
	while(head && is_spaces(head ->content))
		head = head->next;

	if(!head || !ft_strcmp(head ->content, "~"))
	{
		new_path = getenv("HOME");
		ft_cd(new_path);
	}
	else if(!ft_strcmp(head->cmd[1], "-"))
	{
		printf("%s\n", getcwd(NULL, 0));
	}
	else if(!ft_strcmp(head->cmd[1], ".."))
		ft_cd("..");
	else if(!ft_strcmp(head->cmd[1], "."))
		ft_cd(".");
	else if(!ft_strcmp(head->cmd[1], "/"))
		ft_cd("/");
	else
		ft_cd(head->cmd[1]);
	return (0);
}
int rendering_cd(t_list *list)
{
	if(list  == NULL)
		return (0);
	// int i= 0;
	print_double_list(list);
	ft_check_args_of_cd(list);
	return (0);
}