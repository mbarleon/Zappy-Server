/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** zap_srv_t
*/

#ifndef ZAP_SRV_T_H_
    #define ZAP_SRV_T_H_
    #include <stddef.h>
    #include <stdint.h>
    #include "zap_srv_socket.h"

/**
 * @struct zap_srv_t
 * @brief Structure representing the configuration of a Zappy server.
 *
 * This structure holds the basic configuration parameters for the server,
 * including the network port, the server's frequency and its socket.
 */
typedef struct {
    /**
     * @brief The network port number on which the server listens
     * (16-bit unsigned integer).
     */
    uint16_t port;
    /**
     * @brief The frequency at which the server operates (size_t).
     */
    size_t frequency;
    /**
     * @brief The socket of the server.
     */
    zap_srv_socket_t sock;
} zap_srv_t;

#endif /* !ZAP_SRV_T_H_ */
