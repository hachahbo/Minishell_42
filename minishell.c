/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:55:43 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/08 10:36:12 by amoukhle         ###   ########.fr       */
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
    char *input;
	t_list *head;
	t_list *env_list;
	t_list *new_list;
	t_list	*new_list_w_s;

	head = NULL;
	new_list_w_s = NULL;
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
			if (ft_valid_command(head) == 0)
			{
				ft_make_new_list(head, &new_list, env_list);
				ft_make_new_list_w_s(new_list, &new_list_w_s);
				printlist(new_list_w_s);
				ft_builtins(new_list_w_s, env_list);
				ft_lstclear(&head);
				ft_lstclear(&new_list);
				ft_lstclear(&new_list_w_s);
			}
			else
				ft_lstclear(&head);
			if(strlen(input) > 0)
				add_history(input);
			free(input);
		}
		// system("leaks minishell");
	}
	ft_lstclear(&env_list);
	return (0);
}