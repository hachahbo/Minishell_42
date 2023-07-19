/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:55:43 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/19 04:03:21 by amoukhle         ###   ########.fr       */
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
		// print_double_list(last_list);
		// printlist(head);
		ft_execution(last_list, env_list, vars);
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

int	get_value(int value)
{
	static int v;

	if (value != -1)
		v = value;
	return (v);
}


void	nothing_minishell(int sig)
{
	(void)sig;
}

void	nothing(int sig)
{
	(void)sig;

	write(1, "\n", 1);
}


void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		state_exit = 1;
	}
}

void	ft_change_all_d_s(t_list *env_list, char *new_shlvl, int i)
{
	while (env_list)
	{
		free(env_list->cmd[i]);
		env_list->cmd[i] = new_shlvl;
		env_list = env_list->next;
	}
}

int	ft_isall_string_num(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	ft_change_value_of_shlvl(char *value, t_list *env_list, t_list *tm, int i)
{
	int		lvl;
	char	*tmp;
	char	*new_shlvl;
	
	lvl = ft_atoi(value) + 1;
	tmp = ft_itoa(lvl);
	new_shlvl = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	free(env_list->content);
	env_list->content = new_shlvl;
	ft_change_all_d_s(tm, new_shlvl, i);
}

void	ft_change_shlvl(t_list *env_list)
{
	char	*value;
	int		i;
	t_list	*tm;

	tm = env_list;
	value = NULL;
	i = 0;
	while (env_list)
	{
		if (ft_strncmp("SHLVL=", env_list->content, ft_strlen("SHLVL=")) == 0)
		{
			value = &env_list->content[ft_strlen("SHLVL=")];
			break;
		}
		env_list = env_list->next;
		i++;
	}
	if (!value || ft_isall_string_num(value))
		return ;
	ft_change_value_of_shlvl(value, env_list, tm, i);
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
	ft_change_shlvl(env_list);
	state_exit = 0;
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
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
	}
	ft_lstclear(&env_list);
	return (0);
}
