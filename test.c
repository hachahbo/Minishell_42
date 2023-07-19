/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:05:41 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/19 04:00:02 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *line;

    printf("Enter some text (Ctrl+D to end input):\n");

    while ((line = readline("> ")) != NULL) {
        // Process the input line (if needed)
        // ...

        // Add the input to history
        add_history(line);

        // Free the readline buffer
        free(line);
    }

    printf("EOF (Ctrl+D) detected. Input has ended.\n");

    return 0;
}




