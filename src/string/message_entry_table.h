/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** message_entry_table
*/

#ifndef ZAP_SRV_MESSAGE_ENTRY_TABLE_H_
    #define ZAP_SRV_MESSAGE_ENTRY_TABLE_H_

typedef enum {
    ZAP_SRV_MSG_MIN = 0,

    ZAP_SRV_WELCOME,

    ZAP_SRV_MSG_MAX
} zap_srv_msg_entries_t;

const char *fetch_msg(const zap_srv_msg_entries_t entry);

#endif /* !ZAP_SRV_MESSAGE_ENTRY_TABLE_H_ */
