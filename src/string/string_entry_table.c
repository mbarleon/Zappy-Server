/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** string_entry_table
*/

#include "string_entry_table.h"

/**
 * @brief Table of constant strings used for various server messages and
 * errors.
 *
 * This static array contains string literals for error messages, usage
 * instructions, and other informational messages used throughout the server
 * codebase.
 * The first and last entries serve as placeholders for missing strings.
 *
 * Entries include:
 * - General error messages (e.g., "socket failed.", "bind failed.")
 * - Server status messages (e.g., "Server listening on %s:%d.")
 * - Usage instructions for the server executable
 * - Exception handling messages
 *
 * @note The array is intended for internal use within the string_entry_table
 * module.
 */
static const char *string_table[] = {
    "Missing string in string entry table.",

    "socket failed.",
    "accept failed.",
    "poll failed.",
    "bind failed.",
    "getsockname failed.",
    "listen failed.",
    "Server listening on %s:%d.",
    "Stopping server...",
    "%d SIGINT or SIGTERM detected, aborting.",
    ("USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c "
        "clientsNb -f freq\n"),
    "Caught exception in %s: %s.",
    "Max clients reached.",
    "Client with fd %d connected: %s:%d",
    "Client with fd %d exited unexpectedly.",
    "Disconnecting client with fd %d.",

    "Missing string in string entry table."
};

/**
 * @brief Retrieves a string from the string table based on the given entry.
 *
 * This function returns the string corresponding to the specified
 * zap_srv_string_entries_t entry from the string_table array. If the entry
 * is out of bounds (less than or equal to ZAP_SRV_STRING_MIN or greater than
 * or equal to ZAP_SRV_STRING_MAX), it returns the string at
 * string_table[ZAP_SRV_STRING_MAX] as a fallback.
 *
 * @param entry The enum value representing the string entry to fetch.
 * @return const char* The corresponding string from the string table, or
 *         the fallback string if the entry is invalid.
 */
const char *fetch_string(const zap_srv_string_entries_t entry)
{
    if (entry <= ZAP_SRV_STRING_MIN || entry >= ZAP_SRV_STRING_MAX) {
        return string_table[ZAP_SRV_STRING_MAX];
    }
    return string_table[entry];
}
