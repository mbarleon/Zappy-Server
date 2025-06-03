/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** server_internal
*/

#ifndef ZAP_SRV_SERVER_INTERNAL_H_
    #define ZAP_SRV_SERVER_INTERNAL_H_
    #include "server.h"
    #include <stdlib.h>
    #include <signal.h>
    #include <stdbool.h>
    #include <cextend/macro.h>
    #include <cextend/logger.h>
    #define ZAP_SRV_MAX_SIGINT 3

bool keep_running(bool running);
void handle_sigint(UNUSED int sig, UNUSED siginfo_t *info,
    UNUSED void *ucontext);

#endif /* !ZAP_SRV_SERVER_INTERNAL_H_ */
