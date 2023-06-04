/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 19:11:14 by hachahbo          #+#    #+#             */
/*   Updated: 2023/06/03 16:54:52 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libc.h>
# include <stdio.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

void	ft_make_list(char *input, t_list **head);
void	make_env_list(char **env, t_list **env_list);
int		is_spaces(char *str);
char 	*skip_spaces(char *input);
char	*check_data(char *input, int *start, int *end);
void	ft_status(t_list *new, int *flag1, int *flag2);
int		ft_strcmp(char *s1, char *s2);
int		is_spaces(char *str);
int 	ft_strisspace(const char* str);
char	*skip_spaces(char *input);
int		ft_echo(t_list *env_list, t_list *head);
int		check_d_quote(t_list *head);
int		ft_empty(t_list *head);
int		check_pipes(t_list *head);
int		check_redirection(t_list *head);
void	ft_status(t_list *new, int *flag1, int *flag2);
char	*check_data(char *input, int *start, int *end);
void	printlist(t_list *head);
void	ft_lstclear(t_list **lst);
void	ft_env(t_list *env_list);
void	ft_make_new_list(t_list *head, t_list **new_list);
char	*ft_pwd(t_list *env_list);
void	ft_cd(char *path);
char	*delete_d_quot(char *str);
void	ft_new_list_wihtout_d_quot(t_list *new_list, t_list **new_list_w_d_q);
#endif

