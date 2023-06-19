# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 15:02:26 by hachahbo          #+#    #+#              #
#    Updated: 2023/06/19 23:11:30 by amoukhle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -Wall -Werror - Wextra

CC = cc
# CFLAGS = -Werror -Wall -Wextra

OBJS = minishell.o make_list.o ft_space.o ft_echo.o \
		d_quotes.o check_pipes.o redirections.o status.o \
		check_data.o helper.o ft_env.o ft_pwd.o ft_cd.o \
		builtins.o ft_last_list.o ft_make_new_list.o\
		ft_node.o ft_expand_env.o ft_tools.o\

RM = rm -f

all : $(NAME)
	@echo "																	 "			
	@echo "███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░"
	@echo "████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░"
	@echo "██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░"
	@echo "██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░"
	@echo "██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗"
	@echo "╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "																	 "			

$(NAME) : $(OBJS)
	@cd libft && make
	@$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME) -lreadline
	
$(OBJS) : minishell.h

clean :
	@cd libft && make clean
	@$(RM) $(OBJS)

fclean : clean
	@cd libft && make fclean
	@$(RM) $(NAME)
	
re : fclean all