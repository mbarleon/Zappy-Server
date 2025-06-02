/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** parse_args_internal
*/

#ifndef ZAP_SRV_PARSE_ARGS_INTERNAL_H_
    #define ZAP_SRV_PARSE_ARGS_INTERNAL_H_
    #include <errno.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <stdbool.h>
    #include "parse_args.h"
    #include "cextend/macro.h"
    #include "cextend/exception.h"

    #define ZAP_SRV_FLAG_LEN 6

/**
 * @enum zap_srv_flags_t
 * @brief Enumeration of server flag types used for parsing command-line
 * arguments.
 *
 * This enum defines the possible flags that can be encountered when parsing
 * arguments for the Zappy server. Each value corresponds to a specific flag:
 * - ZAP_SRV_FLAG_UNKNOWN: Represents an unknown or unrecognized flag.
 * - ZAP_SRV_FLAG_P: Represents the '-p' flag (typically for port).
 * - ZAP_SRV_FLAG_X: Represents the '-x' flag (typically for map width).
 * - ZAP_SRV_FLAG_Y: Represents the '-y' flag (typically for map height).
 * - ZAP_SRV_FLAG_N: Represents the '-n' flag (typically for team names).
 * - ZAP_SRV_FLAG_C: Represents the '-c' flag (typically for client count).
 * - ZAP_SRV_FLAG_F: Represents the '-f' flag (typically for frequency).
 */
typedef enum {
    ZAP_SRV_FLAG_UNKNOWN = -1,
    ZAP_SRV_FLAG_P,
    ZAP_SRV_FLAG_X,
    ZAP_SRV_FLAG_Y,
    ZAP_SRV_FLAG_N,
    ZAP_SRV_FLAG_C,
    ZAP_SRV_FLAG_F
} zap_srv_flags_t;

zap_srv_flags_t handle_c_flag(const char **av, zap_srv_parsed_context_t *ctxt,
    int *i);
zap_srv_flags_t handle_f_flag(const char **av, zap_srv_parsed_context_t *ctxt,
    int *i);
zap_srv_flags_t handle_n_flag(const char **av, zap_srv_parsed_context_t *ctxt,
    int *i);
zap_srv_flags_t handle_p_flag(const char **av, zap_srv_parsed_context_t *ctxt,
    int *i);
zap_srv_flags_t handle_x_flag(const char **av, zap_srv_parsed_context_t *ctxt,
    int *i);
zap_srv_flags_t handle_y_flag(const char **av, zap_srv_parsed_context_t *ctxt,
    int *i);

size_t get_size_t_from_str(const char *str);
uint16_t get_uint16_from_str(const char *str);

#endif /* !ZAP_SRV_PARSE_ARGS_INTERNAL_H_ */
