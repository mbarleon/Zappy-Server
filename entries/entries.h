/*
** EPITECH PROJECT, 2025
** lib-cextend
** File description:
** cextend_log_init_entry
*/

#ifndef CEXTEND_ENTRIES_H_
    #define CEXTEND_ENTRIES_H_
    #include <cextend/macro.h>
    /**
     * @enum cextend_constructor_priotiries_t
     * @brief Enumerates the constructor priorities for various components.
     *
     * This enumeration defines priority values for different initialization
     * entries used in the system. The priorities can be used to determine
     * the order in which components are initialized.
     *
     * @var CEXTEND_MIN_ENTRY
     *      The minimum entry value for constructor priorities
     *      (starting at 101).
     * @var ZAP_SRV_INIT_SIGINT_ENTRY
     *      Priority for initializing sigint handler.
     * @var ZAP_SRV_INIT_RAND_ENTRY
     *      Priority for initializing the random number generator for the
     *      Zappy server.
     * @var CEXTEND_INIT_LOG_ENTRY
     *      Priority for initializing the logging system.
     * @var CEXTEND_INIT_MEMORY_ENTRY
     *      Priority for initializing the memory management system.
     */

typedef enum {
    CEXTEND_MIN_ENTRY = 101,
    ZAP_SRV_INIT_SIGINT_ENTRY,
    ZAP_SRV_INIT_RAND_ENTRY,
    CEXTEND_INIT_LOG_ENTRY,
    CEXTEND_INIT_MEMORY_ENTRY
} cextend_constructor_priotiries_t;

void initialize_log_entry(void);
void initialize_memory_entry(void);
void initialize_srand_entry(void);
void init_sigint_handler(void);

#endif /* !CEXTEND_ENTRIES_H_ */
