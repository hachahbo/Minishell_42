/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 19:11:14 by hachahbo          #+#    #+#             */
/*   Updated: 2023/07/16 23:20:44 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libc.h>
# include <stdio.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "libft/libft.h"

int	state_exit;

void	ft_make_list(char *input, t_list **head, t_var *vars);
void	make_env_list(char **env, t_list **env_list);
int		is_spaces(char *str);
char 	*skip_spaces(char *input);
char	*check_data(char *input, int *start, int *end);
void	ft_status(t_list *new, int *flag1, int *flag2);
int		ft_strcmp(char *s1, char *s2);
int		is_spaces(char *str);
int		ft_strisspace(const char* str);
char	*skip_spaces(char *input);
int		check_d_quote(t_list *head);
int		ft_empty(t_list *head);
int		check_pipes(t_list *head);
int		check_redirection(t_list *head);
void	ft_status(t_list *new, int *flag1, int *flag2);
char	*check_data(char *input, int *start, int *end);
void	printlist(t_list *head);
void	print_double_list(t_list *head);
void	ft_lstclear(t_list **lst);
// void	ft_env(t_list *env_list);
void	ft_env(t_env *env_list);
void	ft_make_new_list(t_list *head, t_list **new_list, t_list *env_list);
void	ft_pwd(t_list *env_list);
void	ft_cd(char *path);
char	*ft_expand_value(char *str, t_list *env_list);
int		rendering_cd(t_list *list);
int		ft_echo(t_list *head);
int		ft_builtins(t_list *list, t_list *env_list, t_env *help);
char	*handle_env(t_list *list, t_list *env_list, int num_env);
int		serche_for_DOC(t_list *list);
void	ft_make_new_list_w_s(t_list *new_list, t_list **new_list_w_s);
int		skip_node(t_list *head, int num_env);
void	add_node(t_list **new_list, char *str, int in_join);
void	ft_finale_list(t_list *new_list_w_s, t_list **last_list);
int		count_arg(t_list *new_list_w_s);
void	free_double(char **str);
void	get_command(t_list *new_list_w_s, t_list **last_list);
void	sit_type(t_list *list);
void	ft_split_list(t_list **new_list_w_s, t_list **last_list, int *is_cmd, int *is_doc);
void	parser(t_list *head, t_list *env_list, char *input, t_env *help);
void	affiche_error(void);
int		is_DOC(t_list *list);
char	*generate_value_of_env(char *str, char *tmp, t_list_str **list_str, t_list **new_list);
char	*join_list_str(char *s1, char *s2, t_list_str **list_str);
int		join_node(t_list *head);
void	ft_skip_node(t_var *var, t_list *head);
void	creat_word(t_list *head, t_list **new_list, t_list_str	**list_str, t_var *var);
int		is_word(t_list *head);
void	get_command_and_arg(char **cmd, t_list *new_list_w_s);
void	get_pipe(t_list *new_list_w_s, t_list **last_list);
void	get_DOC(t_list **new_list_w_s, t_list **last_list);
int		ft_open_infile(t_list *node, t_var *var, t_list *env_list);
char	*get_string_DOC(t_list *list, t_var *var, t_list *env_list, t_list_str *list_str);
void	ft_skip_node_DOC(t_list *list, t_var *var);
int		skip_node_DOC(t_list *list, t_var *var);
void	ft_init_var(t_var *var);
char	*handle_env_DOC(t_list *list, t_list *env_list, int num_env);
int     is_spaces_char(char c);
int		ft_export(t_list *head, t_env *env_list);
void	ft_lstclear_env(t_env **lst);
void    make_copy_env_list(t_list *env_list, t_env **new_env_list);
void    make_copy_env_list_char(char **env, t_env **new_env_list);
char	*until_equal_or_plus(char *big_str, char c);
void	add_node_to_list(t_env **head, t_env *new);
void	remove_node(t_env **head, char *min);
t_env	*find_small(t_env *list);
int		check_double_nodes(t_list *new, t_list **env_list);
t_env	*ft_lstnew_env(char *str);
int	    check_the_plus(char *str);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstlast_env(t_env *lst);
int	    check_double_key(t_env *new_list, t_env *new_env);
int		check_is_valid(t_env *new_env);
#endif

