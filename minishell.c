/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:55:43 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/19 04:59:00 by hachahbo         ###   ########.fr       */
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
	tmp->num_env = 0;
	tmp->skip = 0;
	tmp->in_join = 0;
	return (tmp);
}

void	parser(t_list *head, t_list *env_list, char *input, t_env *help)
{
	t_list	*new_list;
	t_list	*new_list_w_s;
	t_list	*last_list;
	t_var	*vars;

	new_list = NULL;
	new_list_w_s = NULL;
	last_list = NULL;
	vars = init_vars();
	ft_make_list(input, &head, vars);
	if (ft_valid_command(head) == 0)
	{
		ft_make_new_list(head, &new_list, env_list);
		ft_make_new_list_w_s(new_list, &new_list_w_s);
		// printlist(head);
		ft_finale_list(new_list_w_s, &last_list);
		// print_double_list(last_list);
		// ft_open_infile(last_list, vars, env_list);
		ft_builtins(last_list, env_list, help);
		ft_lstclear(&head);
		ft_lstclear(&new_list);
		ft_lstclear(&new_list_w_s);
		ft_lstclear(&last_list);
		system("leaks minishell");
		free(vars);
	}
	else
	{
		ft_lstclear(&head);
		free(vars);
	}
	if(strlen(input) > 0)
		add_history(input);
	free(input);
}
// void f()
// {
// 	system("leaks minishell");

// }
int main(int ac, char **av, char **env)
{
	char	*input;
	t_list	*head;
	t_list	*env_list;
	t_env	*help_list = NULL;

	(void)ac;
	(void)av;
	// atexit(f);
	head = NULL;
	make_env_list(env, &env_list);
	make_copy_env_list_char(env, &help_list);
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
			parser(head, env_list, input, help_list);
		else
			free(input);
	}
	ft_lstclear(&env_list);
	return (0);
}