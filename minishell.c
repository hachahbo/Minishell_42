/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:55:43 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/06 14:07:25 by hachahbo         ###   ########.fr       */
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
	(void) ac;
	(void) av;
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
		if(ft_strisspace(input) == 0)
		{
			ft_make_list(input, &head);
				// printlist(head);
			if(ft_valid_command(head) == 0)
			{
				// puts("-----------2end list ----------");
				ft_make_new_list(head, &new_list);
					// printlist(new_list);
				// puts("-----------3erd list ----------");
				ft_new_list_wihtout_d_quot(new_list, &new_list_w_d_q);
					//printlist(new_list_w_d_q);
				ft_builtins(new_list_w_d_q, env_list);
				ft_lstclear(&head);
				ft_lstclear(&new_list);
				ft_lstclear(&new_list_w_d_q);
			}
			if(strlen(input) > 0)
				add_history(input);
			free(input);
		}
	}
	ft_lstclear(&env_list);
	exit (0);
    return (0);
}