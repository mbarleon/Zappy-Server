/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** utils
*/

#ifndef ZAP_SRV_UTILS_H_
    #define ZAP_SRV_UTILS_H_
    #include "types.h"
    #include <stdlib.h>
    #include <stddef.h>
    #include <stdbool.h>

bool is_valid_char(char c);
zap_srv_pos_t *generate_shuffled_positions(ssize_t x, ssize_t y);

#endif /* !ZAP_SRV_UTILS_H_ */
