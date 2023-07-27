/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:55:43 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/27 13:48:48 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_valid_command(t_list *head)
{
	if(check_d_quote(head))
		return (1);
	if(check_redirection(head))
		return (1);
	if(check_num_herdoc(head))
		return (1);
	if(check_pipes(head))
		return (1);
	return (0);
}

t_var *init_vars(t_env *env_list)
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


void	parser(t_list *head, t_env **env_list, char *input)
{
	t_list	*new_list;
	t_list	*new_list_w_s;
	t_list	*last_list;
	t_var	*vars;

	new_list = NULL;
	new_list_w_s = NULL;
	last_list = NULL;
	vars = init_vars(*env_list);
	ft_make_list(input, &head, vars);
	if (ft_valid_command(head) == 0)
	{
		ft_make_new_list(head, &new_list, *env_list);
		ft_make_new_list_w_s(new_list, &new_list_w_s);
		ft_finale_list(new_list_w_s, &last_list);
		// print_double_list(new_list);
		// printlist(head);
		ft_execution(last_list, env_list, vars);
		// ft_builtins(last_list, env_list);
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
	if (sig == SIGINT)
		write(1, "\n", 1);
	else if (sig == SIGQUIT)
		write(1, "Quit: 3\n", 8);
}


void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (get_value(-1) == 3)
		{
			close(0);
			get_value(4);
			state_exit = 1;
		}
		else
		{
			write( 1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			state_exit = 1;
			get_value(1);
		}
	}
	else if (sig == SIGQUIT)
	{
		(void)sig;
	}
}

void	ft_change_all_d_s(t_env *env_list, char *new_shlvl, int i)
{
	while (env_list)
	{
		free(env_list->env[i]);
		env_list->env[i] = ft_strdup(new_shlvl);
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

void	ft_change_value_of_shlvl(char *value, t_env *env_list, t_env *tm, int i)
{
	int		lvl;
	char	*tmp;
	char	*new_shlvl;
	
	lvl = ft_atoi(value) + 1;
	tmp = ft_itoa(lvl);
	new_shlvl = ft_strjoin("SHLVL=", tmp);
	free(env_list->content);
	env_list->content = new_shlvl;
	free(env_list->val);
	env_list->val = ft_strdup(tmp);
	free(tmp);
	ft_change_all_d_s(tm, new_shlvl, i);
}

void	ft_change_shlvl(t_env *env_list)
{
	char	*value;
	int		i;
	t_env	*tm;

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
	if (!value)
		return ;
	ft_change_value_of_shlvl(value, env_list, tm, i);
}

int	check_the_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

char	*delete_back_slash(char *str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	while (str[i])
		i++;
	s = (char *)malloc(i + 1);
	j = 0;
	i = 0;
	while (str[j])
	{
		if (str[j] == '\\')
			j++;
		s[i] = str[j];
		i++;
		j++;
	}
	s[i] = '\0';
	return (s);
}

t_env	*ft_lstnew_env(char *str, char **env)
{
	t_env	*tmp;
	char	*key;
	char	*val;

	tmp = (t_env *)malloc(sizeof(t_env));
	if (!tmp)
		return (0);
	if (!str)
		return (tmp->key = ft_strdup("000"), tmp);
	key = until_equal_or_plus(str, '=');
	tmp->plus = 0;
	if (check_the_plus(key))
	{
		tmp->plus = '+';
		free(key);
		key = until_equal_or_plus(str, '+');
	}
	val = ft_strchr(str, '=');
	if (val)
	{
		val = delete_back_slash(val);
		tmp->c = val[0];
	}
	tmp->hide_path = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	tmp->content = ft_strdup(str);
	tmp->key = key;
	tmp->env = ft_str_double_dup(env);
	if (val == 0)
		tmp->val = ft_strdup(NULL);
	else
		tmp->val = ft_strdup(val + 1);
	tmp->next = 0;
	free(val);
	return (tmp);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	t_env	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	while (tmp->next != 0)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;
	int		i;

	i = 0;
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast_env(*lst);
	tmp->next = new;
}

char	**creat_env(void)
{
	char	**env;
	char	*str;

	env = (char **)malloc((sizeof(char *) * 4));
	if (!env)
		affiche_error();
	str = getcwd(NULL, 0);
	env[0] = ft_strjoin(("PWD="), str);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	free(str);
	return(env);
}

void	make_copy_env_list_char(char **env, t_env **new_env_list)
{
	t_env	*new_env;
	int		i;
	char	*str;
	char	*get_cwd;

	i = 0;
	if (!env[i])
	{
		env = creat_env();
		get_cwd = getcwd(NULL, 0);
		str = ft_strjoin(("PWD="), get_cwd);
		new_env = ft_lstnew_env(str, env);
		ft_lstadd_back_env(new_env_list, new_env);
		free(str);
		str = ft_strdup("SHLVL=1");
		new_env = ft_lstnew_env(str, env);
		ft_lstadd_back_env(new_env_list, new_env);
		free(str);
		str = ft_strjoin(("_="), "/usr/bin/env");
		new_env = ft_lstnew_env(str, env);
		ft_lstadd_back_env(new_env_list, new_env);
		free(str);
		str = ft_strdup("OLDPWD");
		new_env = ft_lstnew_env(str, env);
		ft_lstadd_back_env(new_env_list, new_env);
		free(str);
		free_double(env);
		free(get_cwd);
	}
	else
	{
		while (env[i])
		{
			new_env = ft_lstnew_env(env[i], env);
			ft_lstadd_back_env(new_env_list, new_env);
			i++;
		}
	}
}

int main(int ac, char **av, char **env)
{
	char	*input;
	t_list	*head;
	t_env	*env_list;
	int		std_in;

	if (ac != 1)
	{
		write (2, "bash: ", 6);
		write (2, av[1], ft_strlen(av[1]));
		write (2, ": No such file or directory\n", 28);
		exit(1);
	}
	head = NULL;
	env_list = NULL;
	make_copy_env_list_char(env, &env_list);
	ft_change_shlvl(env_list);
	state_exit = 0;
	rl_catch_signals = 0;
	std_in = dup(0);
	while(1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		get_value(0);
		dup2(std_in,0);
		input = readline("[minishell][$]~> ");
		if (!input)
		{
			write(1, "exit\n", 5);
			clear_history();
			exit (0);
		}
		
		if(ft_strisspace(input) == 0)
			parser(head, &env_list, input);
		else
			free(input);
		// system("leaks minishell")
	}
	return (0);
}
