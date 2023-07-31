# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 15:02:26 by hachahbo          #+#    #+#              #
#    Updated: 2023/07/31 13:02:30 by amoukhle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# CC = cc -Wall -Werror - Wextra

CC = cc
CFLAGS = -Werror -Wall -Wextra #-fsanitize=address -g3

OBJS = minishell.o make_list.o ft_space.o ft_echo.o \
		d_quotes.o check_pipes.o redirections.o status.o \
		check_data.o helper.o ft_env.o ft_pwd.o ft_cd.o \
		builtins.o ft_last_list.o ft_make_new_list.o\
		ft_node.o ft_expand_env.o ft_tools.o\
		ft_open_infile.o ft_handle_option_DOC.o\
		ft_open_outfile.o ft_open_append_file.o\
		ft_open_heredoc.o ft_in_heredoc.o ft_node_heredoc.o\
		ft_execution.o ft_spaces_split.o ft_export.o\
		ft_handle_signals.o ft_error.o ft_tools_for_cmd.o\
		ft_tools_for_DOC.o ft_wait_func.o ft_pipe.o\
		ft_tools_for_list.o ft_init.o ft_treatment_env.o\
		ft_more_tools.o builtins_two.o\
		ft_cd_two.o ft_export_three.o ft_export_two.o\

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
	@$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME) -lreadline -L$(shell brew --prefix readline)/lib
	
%.o : %.c minishell.h
	$(CC) $(CFLAGS) -I$(shell brew --prefix readline)/include -c $< -o $@
	
clean :
	@cd libft && make clean
	@$(RM) $(OBJS)

fclean : clean
	@cd libft && make fclean
	@$(RM) $(NAME)
	
re : fclean all