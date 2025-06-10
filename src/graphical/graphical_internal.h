/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** graphical_internal
*/

#ifndef ZAP_SRV_GRAPHICAL_INTERNAL_H_
    #define ZAP_SRV_GRAPHICAL_INTERNAL_H_
    #include <string.h>
    #include <stdlib.h>
    #include "graphical.h"
    #include "../server/server.h"
    #include <cextend/snprintf_alloc.h>

/**
 * @struct zap_srv_graph_args_s
 * @brief Structure holding arguments for the graphical server in Zappy.
 *
 * This structure contains various size and sign-related parameters used
 * internally by the graphical server.
 */
typedef struct zap_srv_graph_args_s {
    /**
     * @brief Indicates whether the arguments are signed.
     */
    bool is_signed;
    /**
     * @brief Number of arguments.
     */
    size_t nargs;
    /**
     * @brief Signed size parameter A.
     */
    ssize_t ssize_a;
    /**
     * @brief Signed size parameter B.
     */
    ssize_t ssize_b;
    /**
     * @brief Unsigned size parameter A.
     */
    size_t size_a;
    /**
     * @brief Unsigned size parameter B.
     */
    size_t size_b;
} zap_srv_graph_args_t;

#endif /* !ZAP_SRV_GRAPHICAL_INTERNAL_H_ */
