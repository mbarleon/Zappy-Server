/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** compute_density
*/

#include "map_internal.h"

/**
 * @brief Initializes a zap_srv_dentity_table_t array with default values.
 *
 * This function sets each entry in the provided table to a specific entity
 * type (FOOD, LINEMATE, DERAUMERE, SIBUR, MENDIANE, PHIRAS, THYSTAME) with a
 * quantity of 0.0F.
 * The function does nothing if the provided table pointer is NULL.
 *
 * @param table Pointer to an array of zap_srv_dentity_table_t to initialize.
 */
static void create_null_table(zap_srv_dentity_table_t *table)
{
    if (!table) {
        return;
    }
    table[0] = (zap_srv_dentity_table_t){FOOD, 0.0F};
    table[1] = (zap_srv_dentity_table_t){LINEMATE, 0.0F};
    table[2] = (zap_srv_dentity_table_t){DERAUMERE, 0.0F};
    table[3] = (zap_srv_dentity_table_t){SIBUR, 0.0F};
    table[4] = (zap_srv_dentity_table_t){MENDIANE, 0.0F};
    table[5] = (zap_srv_dentity_table_t){PHIRAS, 0.0F};
    table[6] = (zap_srv_dentity_table_t){THYSTAME, 0.0F};
}

/**
 * @brief Counts the occurrences of each element type in a linked list and
 * updates their density in the table.
 *
 * Iterates through the given linked list of elements and increments the
 * density count for each element type in the provided density table.
 *
 * @param element Pointer to the head of the linked list of elements.
 * @param table Pointer to the density table where the count for each element
 * type will be incremented.
 */
static void count_element_types(const zap_srv_elements_list_t *element,
    zap_srv_dentity_table_t *table)
{
    for (const zap_srv_elements_list_t *tmp = element; tmp; tmp = tmp->next) {
        table[tmp->element].density++;
    }
}

/**
 * @brief Computes the density table of elements on the map.
 *
 * This function allocates and initializes a density table for all element
 * types defined by ZAP_SRV_ELEMENTS_QUANTITY. It iterates over the map's
 * elements, counting the occurrences of each element type and then normalizes
 * these counts by dividing by the total map size to obtain densities.
 *
 * @param map Pointer to the zap_srv_map_t structure representing the map.
 * @return Pointer to a newly allocated zap_srv_dentity_table_t array
 * containing the density of each element type, or NULL on allocation failure
 * or if the map size is zero.
 */
zap_srv_dentity_table_t *compute_density(const zap_srv_map_t *map)
{
    const size_t map_size = map->x * map->y;
    zap_srv_dentity_table_t *table = (zap_srv_dentity_table_t *)
        malloc(sizeof(zap_srv_dentity_table_t) * ZAP_SRV_ELEMENTS_QUANTITY);

    if (!table || map_size == 0) {
        return NULL;
    }
    create_null_table(table);
    if (!map->elements) {
        return table;
    }
    for (size_t i = 0; i < map->x; ++i) {
        for (size_t j = 0; j < map->y; ++j) {
            count_element_types(map->elements[i][j], table);
        }
    }
    for (size_t i = 0; i < ZAP_SRV_ELEMENTS_QUANTITY; ++i) {
        table[i].density /= (float)map_size;
    }
    return table;
}
