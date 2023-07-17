/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoukhle <amoukhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:54:00 by amoukhle          #+#    #+#             */
/*   Updated: 2023/07/17 05:25:31 by amoukhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

volatile sig_atomic_t KEYBOARD_INTERRUPT = 0;

void handleSignal(int signal)
{
    // KEYBOARD_INTERRUPT = 1;
}

int main()
{
    signal(SIGINT, handleSignal);
    printf("Remove ^C on exit!");
    fflush(stdout);
    while (!KEYBOARD_INTERRUPT)
    {
    }
    printf("\b\b\033[K\n");
    fflush(stdout);
    return 0;
}






