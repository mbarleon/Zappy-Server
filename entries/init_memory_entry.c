/*
** EPITECH PROJECT, 2025
** lib-cextend
** File description:
** init_memory_entry
*/

#include "entries.h"
#include <cextend/entries/exception_init.h>

__attribute__((constructor(CEXTEND_INIT_MEMORY_ENTRY)))
static void initialize_memory_entry(void)
{
    should_free_on_abort(true);
}
