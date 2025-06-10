/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** init_rand_entry
*/

#include <time.h>
#include <stdlib.h>
#include "entries.h"

/**
 * @brief Initializes the random number generator for the server.
 *
 * This function is automatically executed before main() due to the
 * constructor attribute. It seeds the random number generator using
 * the current time to ensure different random sequences on each run.
 *
 * @note The constructor priority is set by ZAP_SRV_INIT_RAND_ENTRY.
 */
__attribute__((constructor(ZAP_SRV_INIT_RAND_ENTRY)))
static void initialize_srand_entry(void)
{
    srand((unsigned int)time(NULL));
}
