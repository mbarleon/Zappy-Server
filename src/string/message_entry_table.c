/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** message_entry_table
*/

#include "message_entry_table.h"

/**
 * @brief Table of constant strings used for various server messages and
 * errors.
 *
 * This static array contains string literals for error messages, usage
 * instructions, and other informational messages used throughout the server
 * codebase.
 * The first and last entries serve as placeholders for missing strings.
 *
 * @note The array is intended for internal use within the message_entry_table
 * module.
 */
static const char *message_table[] = {
    "ko\n",

    "WELCOME\n",

    "ko\n"
};

/**
 * @brief Retrieves a string from the string table based on the given entry.
 *
 * This function returns the string corresponding to the specified
 * zap_srv_string_entries_t entry from the string_table array. If the entry
 * is out of bounds (less than or equal to ZAP_SRV_MSG_MIN or greater than
 * or equal to ZAP_SRV_MSG_MAX), it returns the string at
 * message_table[ZAP_SRV_MSG_MAX] as a fallback.
 *
 * @param entry The enum value representing the string entry to fetch.
 * @return const char* The corresponding string from the string table, or
 * the fallback string if the entry is invalid.
 */
const char *fetch_msg(const zap_srv_msg_entries_t entry)
{
    if (entry <= ZAP_SRV_MSG_MIN || entry >= ZAP_SRV_MSG_MAX) {
        return message_table[ZAP_SRV_MSG_MAX];
    }
    return message_table[entry];
}
