/*
** EPITECH PROJECT, 2025
** lib-cextend
** File description:
** init_memory_entry
*/

#include "entries.h"
#include <cextend/entries/exception_init.h>

/**
 * @brief Constructor function to initialize memory entry settings.
 *
 * This function is automatically called before main() due to the
 * constructor attribute. It sets up the memory management behavior
 * by enabling memory to be freed on abort.
 *
 * @note The CEXTEND_INIT_MEMORY_ENTRY macro should resolve to a
 * priority value for the constructor attribute, if needed.
 */
__attribute__((constructor(CEXTEND_INIT_MEMORY_ENTRY)))
static void initialize_memory_entry(void)
{
    should_free_on_abort(true);
}
