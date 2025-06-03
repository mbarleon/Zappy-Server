/*
** EPITECH PROJECT, 2025
** lib-cextend
** File description:
** cextend_log_init_entry
*/

#ifndef CEXTEND_EXITS_H_
    #define CEXTEND_EXITS_H_
    #include <cextend/macro.h>

/**
 * @enum cextend_destructor_priotiries_t
 * @brief Enumerates the priorities for destructor operations in the CEXTEND
 * module.
 *
 * This enum defines the priority levels used to determine the order in which
 * destructors are executed during the exit process. Higher values indicate
 * higher priority.
 *
 * @var CEXTEND_MIN_EXIT
 *      The minimum exit priority value (set to 101).
 * @var CEXTEND_FREE_MEM_EXIT
 *      Priority for freeing memory during exit.
 */
typedef enum {
    CEXTEND_MIN_EXIT = 101,
    CEXTEND_FREE_MEM_EXIT
} cextend_destructor_priotiries_t;

void free_mem_exit(void);

#endif /* !CEXTEND_EXITS_H_ */
