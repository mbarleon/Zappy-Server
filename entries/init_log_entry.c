/*
** EPITECH PROJECT, 2025
** lib-cextend
** File description:
** zap_srv_init_log_entry
*/

#include "entries.h"
#include <cextend/entries/logger_init.h>

/**
 * @brief Constructor function to initialize the log entry system.
 *
 * This function is automatically executed before main() due to the
 * constructor attribute. It is used to perform any necessary
 * initialization for the log entry system by invoking the
 * CEXTEND_INIT_LOG macro or function.
 *
 * @note The CEXTEND_INIT_LOG_ENTRY macro is used as an identifier
 * for the constructor attribute, which may be defined elsewhere.
 */
__attribute__((constructor(CEXTEND_INIT_LOG_ENTRY)))
void initialize_log_entry(void)
{
    CEXTEND_INIT_LOG;
}
