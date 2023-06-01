/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:55:43 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/01 08:49:04 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_valid_command(t_list *head)
{
	if(check_d_quote(head))
		return (1);
	if(check_redirection(head))
		return (1);
	if(check_pipes(head))
		return (1);
	return (0);
}

int main(int ac, char **av, char **env)
{
    char *input;
	t_list *head;
	t_list *env_list;

	head = NULL;
	make_env_list(env, &env_list);
    while(1)
	{
		input = readline("[minishell][$]~> ");
    	if (!input)
		{
			printf("exit\n");
			clear_history();
			exit (1);
		}
		if(ft_strisspace(input))
			break ;
		ft_make_list(input, &head);
		ft_valid_command(head);
		// if(ft_valid_command(head) == 0)
		// 	printlist(head);
		ft_echo(env_list, head);
		ft_lstclear(&head);
		if(strlen(input) > 0)
			add_history(input);
   		free(input);
	}
	ft_lstclear(&env_list);
    return (0);
}
