/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:55:43 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/01 14:15:40 by amoukhle         ###   ########.fr       */
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
	t_list *new_list;

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
		if (ft_valid_command(head))
			break;
		// if(ft_valid_command(head) == 0)
			// printlist(head);
		ft_make_new_list(head, &new_list);
		// printlist(new_list);
		ft_echo(env_list, head);
		ft_lstclear(&head);
		ft_lstclear(&new_list);
		if(strlen(input) > 0)
			add_history(input);
   		free(input);
	}
	ft_lstclear(&env_list);
    return (0);
}
