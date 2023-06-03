/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:55:43 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/03 17:15:08 by amoukhle         ###   ########.fr       */
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

void l()
{
	system("leaks minishell");
}
int main(int ac, char **av, char **env)
{
	// atexit(l);
    char *input;
	t_list *head;
	t_list *env_list;
	t_list *new_list;
	t_list *new_list_w_d_q;

	head = NULL;
	new_list_w_d_q = NULL;
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
		// printf("new: %s\n", delete_d_quot(new_list->content));
		ft_new_list_wihtout_d_quot(new_list, &new_list_w_d_q);
		printlist(new_list_w_d_q);
		// printf("%s\n",ft_pwd(env_list));
		// ft_cd("..");
		// ft_env(env_list);
		// ft_echo(env_list, head);
		ft_lstclear(&head);
		ft_lstclear(&new_list);
		ft_lstclear(&new_list_w_d_q);
		if(strlen(input) > 0)
			add_history(input);
   		free(input);
	}
	ft_lstclear(&env_list);
	exit (0);
    return (0);
}