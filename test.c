/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:05:41 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/16 21:24:43 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void handlers(int num)
{
    rl_on_new_line();
    rl_redisplay();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

int main()
{
	char *line;
	struct sigaction sa;
	sa.sa_handler = handlers;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction(SIGINT, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}
    while (1) {
        line = readline("sssss");
        // Process the line...
        add_history(line);
    }

    return 0;
}

