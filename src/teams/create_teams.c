/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** create_teams
*/

#include "teams_internal.h"

/**
 * @brief Checks if a string contains only valid characters.
 *
 * This function iterates through the given string and verifies that each
 * character is valid.
 *
 * @param str The input string to validate.
 * @return true if all characters in the string are valid; false otherwise.
 */
static bool is_valid_characters(const char *str)
{
    for (size_t i = 0; str[i]; ++i) {
        if (!is_valid_char(str[i])) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Creates a new team and adds it to the linked list of teams.
 *
 * This function allocates and initializes a new zap_srv_team_t structure with
 * the given team name and maximum number of clients. The new team is appended
 * to the end of the teams linked list, unless the list is empty, in which
 * case it becomes the head.
 *
 * The function does not allow creation of a team named "GRAPHIC".
 *
 * @param teams Pointer to the head pointer of the linked list of teams.
 * @param str Name of the team to create. Must not be "GRAPHIC".
 * @param max_clients Maximum number of clients allowed in the team.
 *
 * @throws CEXTEND_EXCEPTION_INVALID_ARGUMENT if teams is NULL or str is
 * "GRAPHIC".
 * @throws CEXTEND_EXCEPTION_BAD_ALLOC if memory allocation fails
 * (via safe_malloc or safe_strdup).
 */
void create_team(zap_srv_team_t **teams, const char *str, size_t max_clients)
{
    zap_srv_team_t *tmp;
    zap_srv_team_t *new_team;

    if (!teams || strcmp(str, "GRAPHIC") == 0 || !is_valid_characters(str)) {
        THROW(CEXTEND_EXCEPTION_INVALID_ARGUMENT);
    }
    new_team = safe_calloc(1, sizeof(zap_srv_team_t), NULL);
    new_team->seg = false;
    new_team->name = safe_strdup(str);
    new_team->max_clients = max_clients;
    if (!*teams) {
        *teams = new_team;
        return;
    }
    for (tmp = *teams; tmp->next; tmp = tmp->next);
    if (!tmp) {
        THROW(CEXTEND_EXCEPTION_INVALID_ARGUMENT);
    }
    tmp->next = new_team;
}
