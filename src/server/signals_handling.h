/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** signals_handling
*/

#ifndef ZAP_SRV_SIGNALS_HANDLING_H_
    #define ZAP_SRV_SIGNALS_HANDLING_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <signal.h>
    #include <stdbool.h>
    #include <cextend/logger.h>
    #include "../string/string_entry_table.h"


    #define ZAP_SRV_MAX_SIGINT 3

bool keep_running(bool running);
void handle_signals(UNUSED int sig, UNUSED siginfo_t *info,
    UNUSED void *ucontext);

#endif /* !ZAP_SRV_SIGNALS_HANDLING_H_ */
