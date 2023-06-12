/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:55:43 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/12 15:12:50 by amoukhle         ###   ########.fr       */
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

t_var *init_vars(void)
{
	t_var	*tmp;
	
	tmp = (t_var *)malloc(sizeof(t_var));
	if (!tmp)
		return (0);
	tmp->end = 0;
	tmp->start = 0;
	tmp->flag1 = 0;
	tmp->flag2 = 0;
	return (tmp);
}

void	parser(t_list *head, t_list *env_list, char *input)
{
	t_list		*new_list;
	t_list		*new_list_w_s;
	t_list		*last_list;
	t_list_str	*list_str;
	t_var		*vars;

	new_list = NULL;
	new_list_w_s = NULL;
	list_str = NULL;
	last_list = NULL;
	vars = init_vars();
	ft_make_list(input, &head, vars);
	if (ft_valid_command(head) == 0)
	{
		ft_make_new_list(head, &new_list, env_list, &list_str);
		ft_make_new_list_w_s(new_list, &new_list_w_s);
		// printlist(new_list_w_s);
		ft_finale_list(new_list_w_s, &last_list);
		print_double_list(last_list);
		// ft_builtins(new_list_w_s, env_list);
		ft_lstclear(&head);
		ft_lstclear(&new_list);
		ft_lstclear(&new_list_w_s);
		ft_lstclear(&last_list);
		list_strclear(&list_str);
		free(vars);
	}
	else
		ft_lstclear(&head);
	if(strlen(input) > 0)
		add_history(input);
	free(input);
}

int main(int ac, char **av, char **env)
{
	char		*input;
	t_list		*head;
	t_list		*env_list;

	head = NULL;
	make_env_list(env, &env_list);
	state_exit = 0;
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
			parser(head, env_list, input);
		// system("leaks minishell");
	}
	ft_lstclear(&env_list);
	return (0);
}