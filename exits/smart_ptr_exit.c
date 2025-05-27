/*
** EPITECH PROJECT, 2025
** lib-cextend
** File description:
** zap_srv_init_log_entry
*/

#include "exits.h"
#include "cextend/exit/memory_exit.h"

__attribute__((destructor(CEXTEND_FREE_MEM_EXIT)))
static void free_mem_exit(void)
{
    free_ptr_list();
}
