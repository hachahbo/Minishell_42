/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:55:43 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/21 21:44:37 by amoukhle         ###   ########.fr       */
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

t_var *init_vars(t_list *env_list)
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
	tmp->q_dq = 0;
	tmp->env_list = env_list;
	return (tmp);
}

void	parser(t_list *head, t_list *env_list, char *input)
{
	t_list	*new_list;
	t_list	*new_list_w_s;
	t_list	*last_list;
	t_var	*vars;
	int		fd;

	new_list = NULL;
	new_list_w_s = NULL;
	last_list = NULL;
	vars = init_vars(env_list);
	ft_make_list(input, &head, vars);
	if (ft_valid_command(head) == 0)
	{
		ft_make_new_list(head, &new_list, env_list);
		ft_make_new_list_w_s(new_list, &new_list_w_s);
		ft_finale_list(new_list_w_s, &last_list);
		print_double_list(last_list);
		// printlist(head);
		// fd = ft_open_heredoc(last_list, vars);
		// unlink("/tmp/here_doc");
		// close(fd);
		// ft_builtins(new_list_w_s, env_list);
		ft_lstclear(&head);
		ft_lstclear(&new_list);
		ft_lstclear(&new_list_w_s);
		ft_lstclear(&last_list);
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

int main(int ac, char **av, char **env)
{
	char	*input;
	t_list	*head;
	t_list	*env_list;

	(void)ac;
	(void)av;
	head = NULL;
	make_env_list(env, &env_list);
	state_exit = 0;
	while(1)
	{
		input = readline("[minishell][$]~> ");
		if (!input || !ft_strcmp(input, "exit"))
		{
			printf("exit\n");
			clear_history();
			exit (1);
		}
		if(ft_strisspace(input) == 0)
			parser(head, env_list, input);
		else
			free(input);
		system("leaks minishell");
	}
	ft_lstclear(&env_list);
	return (0);
}