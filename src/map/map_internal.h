/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** map_internal
*/

#ifndef ZAP_SRV_MAP_INTERNAL_H_
    #define ZAP_SRV_MAP_INTERNAL_H_
    #include "map.h"
    #include "types.h"
    #include <stdlib.h>
    #include <stdbool.h>
    #include "../utils/utils.h"
    #include <cextend/memory.h>

float *compute_density(const zap_srv_map_t *map);

#endif /* !ZAP_SRV_MAP_INTERNAL_H_ */
