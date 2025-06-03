/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** init_sigint_entry
*/

#include <signal.h>
#include <string.h>
#include "entries.h"
#include "../src/server/server_internal.h"

__attribute__((constructor(ZAP_SRV_INIT_SIGINT_ENTRY)))
void init_sigint_handler(void)
{
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = handle_sigint;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa, NULL);
}
