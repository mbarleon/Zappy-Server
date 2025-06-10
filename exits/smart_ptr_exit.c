/*
** EPITECH PROJECT, 2025
** lib-cextend
** File description:
** zap_srv_init_log_entry
*/

#include "exits.h"
#include <cextend/exit/memory_exit.h>

/**
 * @brief Destructor function to free allocated memory on program exit.
 *
 * This function is automatically called when the program terminates,
 * due to the use of the GCC destructor attribute. It ensures that
 * all memory managed by the pointer list is properly released by
 * calling free_ptr_list().
 *
 * @note The attribute parameter (CEXTEND_FREE_MEM_EXIT) specifies
 *       the priority or group for the destructor execution.
 */
__attribute__((destructor(CEXTEND_FREE_MEM_EXIT)))
static void free_mem_exit(void)
{
    free_ptr_list();
}
