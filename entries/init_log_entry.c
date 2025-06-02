/*
** EPITECH PROJECT, 2025
** lib-cextend
** File description:
** zap_srv_init_log_entry
*/

#include "entries.h"
#include <cextend/entries/logger_init.h>

__attribute__((constructor(CEXTEND_INIT_LOG_ENTRY)))
static void initialize_log_entry(void)
{
    CEXTEND_INIT_LOG;
}
