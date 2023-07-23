/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:32:04 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/19 18:32:31 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void signal_handler(int signal) {
    if (signal == SIGINT) {
        // rl_replace_line("", 0); // Clear the input line
        rl_on_new_line();       // Move to a new line
        rl_redisplay();         // Redisplay the prompt
    }
}

int main() {
    signal(SIGINT, signal_handler);

    char *line;

    while (1) {
        line = readline("Enter some text: ");

        if (line == NULL) {
            printf("Ctrl+C received. Input was interrupted.\n");
            break;
        }

        // Process the input line...
        printf("You entered: %s\n", line);

        // Add the input to history
        add_history(line);

        // Free the readline buffer
        free(line);
    }

    return 0;
}
