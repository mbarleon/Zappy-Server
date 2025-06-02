/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** server
*/

#ifndef ZAP_SRV_SERVER_H_
    #define ZAP_SRV_SERVER_H_
    #include <stdint.h>

/**
 * @struct zap_srv_t
 * @brief Structure representing the configuration of a Zappy server.
 *
 * This structure holds the basic configuration parameters for the server,
 * including the network port and the server's frequency.
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
} zap_srv_t;

#endif /* !ZAP_SRV_SERVER_H_ */
