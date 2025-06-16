/*
** EPITECH PROJECT, 2025
** Zappy-Server
** File description:
** generate_map
*/

#include "map_internal.h"

/**
 * @brief Sets the density value for a given element index if it matches the
 * entry in the density table.
 *
 * This function checks if the element at index `j` in the `density_table`
 * matches the element type specified by `i`. If it matches, it sets the value
 * pointed to by `density` to the corresponding density value from the table
 * and returns true. Otherwise, it returns false.
 *
 * @param i The index representing the element type to check
 * (cast to zap_srv_elements_t).
 * @param j The index in the density_table to compare against.
 * @param density Pointer to a float where the density value will be stored
 * if a match is found.
 * @return true if the element matches and density is set, false otherwise.
 */
static bool set_density(size_t i, size_t j, float *density)
{
    if (j == i) {
        *density = density_table[j];
        return true;
    }
    return false;
}

/**
 * @brief Computes the target number of elements to be placed on the map for
 * each element type.
 *
 * This function calculates, for each element type, the number of additional
 * elements that need to be placed on the map to reach the desired density.
 * The desired density for each element is determined using the set_density
 * function, and the current density is provided in the current_density table.
 * The result is stored in the element_targets array.
 *
 * @param[out] element_targets Array where the computed target counts for each
 * element type will be stored.
 * @param[in] current_density Table containing the current density of each
 * element type on the map.
 * @param[in] map_size The total size (number of tiles) of the map.
 *
 * @note The function frees the memory allocated for current_density.
 */
static void compute_element_targets(size_t *element_targets,
    float *current_density, ssize_t map_size)
{
    float density;
    size_t target;
    size_t cur;

    for (size_t i = 0; i < ZAP_SRV_ELEMENTS_QUANTITY && keep_running(false);
        ++i) {
        density = 0.0F;
        for (size_t j = 0; j < ZAP_SRV_ELEMENTS_QUANTITY &&
            !set_density(i, j, &density) && keep_running(false); ++j);
        target = (size_t)(density * (float)map_size + 0.5F);
        cur = (size_t)(current_density[i] * (float)map_size + 0.5F);
        element_targets[i] = (target > cur) ? (target - cur) : 0;
    }
}

/**
 * @brief Adds a new element to the map at the specified position.
 *
 * This function inserts a new element into the linked list of elements
 * at the given (x, y) position on the map. The new element is added to
 * the front of the list. If the new element pointer is NULL, the function
 * does nothing.
 *
 * @param map Pointer to the map structure where the element will be added.
 * @param new_elem Pointer to the new element to add.
 * @param elem The type or identifier of the element to add.
 * @param pos Pointer to the position structure specifying where to add the
 * element.
 */
static void add_elem(zap_srv_map_t *map, zap_srv_elements_list_t *new_elem,
    size_t elem, zap_srv_pos_t *pos)
{
    if (!new_elem) {
        return;
    }
    new_elem->element = (zap_srv_elements_t)elem;
    new_elem->next = map->elements[pos->x][pos->y];
    map->elements[pos->x][pos->y] = new_elem;
}

/**
 * @brief Attempts to place an element on the map at a specified position.
 *
 * This function allocates a new element, initializes its position using the
 * provided positions array and index, and adds it to the map. If memory
 * allocation fails, the function returns false.
 *
 * @param map Pointer to the map structure where the element will be placed.
 * @param positions Array of possible positions for placing elements.
 * @param elem The type or identifier of the element to place.
 * @param pos_idx Index into the positions array specifying where to place the
 * element.
 * @return true if the element was successfully placed, false otherwise.
 */
static bool try_place_elem(zap_srv_map_t *map, zap_srv_pos_t *positions,
    size_t elem, size_t pos_idx)
{
    zap_srv_pos_t pos;
    zap_srv_elements_list_t *new_elem;
    ssize_t x = positions[pos_idx].x;
    ssize_t y = positions[pos_idx].y;

    new_elem = (zap_srv_elements_list_t *)safe_calloc(
        1, sizeof(zap_srv_elements_list_t), NULL);
    if (!new_elem) {
        return false;
    }
    pos = (zap_srv_pos_t){x, y};
    add_elem(map, new_elem, elem, &pos);
    return true;
}

/**
 * @brief Places specified quantities of elements on the map at given
 * positions.
 *
 * Iterates through the elements and their target counts, attempting to place
 * each element on the map at the provided positions until all targets are met.
 * The function cycles through the elements and positions, calling
 * try_place_elem for each placement. Frees the positions array after all
 * elements have been placed.
 *
 * @param map Pointer to the map structure where elements will be placed.
 * @param positions Array of positions where elements can be placed.
 * @param element_targets Array specifying the number of each element to place.
 * @param map_size The total number of available positions in the map.
 */
static void place_elements_on_map(zap_srv_map_t *map, zap_srv_pos_t *positions,
    size_t *element_targets, ssize_t map_size)
{
    size_t elem = 0;
    size_t pos_idx = 0;
    size_t total_to_place = 0;
    size_t placed[ZAP_SRV_ELEMENTS_QUANTITY] = {0};

    for (size_t i = 0; i < ZAP_SRV_ELEMENTS_QUANTITY && keep_running(false);
        ++i)
        total_to_place += element_targets[i];
    while (total_to_place > 0 && keep_running(false)) {
        if (placed[elem] < element_targets[elem]) {
            try_place_elem(map, positions, elem, pos_idx);
            placed[elem]++;
            total_to_place--;
            pos_idx = (pos_idx + 1) % (size_t)map_size;
        }
        elem = (elem + 1) % ZAP_SRV_ELEMENTS_QUANTITY;
    }
}

/**
 * @brief Initializes the map structure by allocating memory for its elements.
 *
 * This function allocates a 2D array of pointers to zap_srv_elements_list_t,
 * based on the dimensions specified in the map (map->x and map->y).
 * Each row of the map is allocated separately.
 *
 * @param map Pointer to the zap_srv_map_t structure to initialize.
 *
 * @note Uses safe_calloc for memory allocation to ensure safety.
 */
static void init_map(zap_srv_map_t *map)
{
    map->elements = (zap_srv_elements_list_t ***)safe_calloc(
        (size_t)map->x, sizeof(zap_srv_elements_list_t **), NULL);
    for (ssize_t i = 0; i < map->x; ++i) {
        map->elements[i] = (zap_srv_elements_list_t **)safe_calloc(
            (size_t)map->y, sizeof(zap_srv_elements_list_t *), NULL);
    }
}

/**
 * @brief Frees the memory allocated for a 2D density array.
 *
 * This function checks if the provided pointer to the density array is valid,
 * and if so, frees the allocated memory and sets the pointer to NULL to avoid
 * dangling pointers.
 *
 * @param density A pointer to the 2D float array to be freed.
 */
static void free_density(float **density)
{
    if (!density || !*density) {
        return;
    }
    free(*density);
    *density = NULL;
}

/**
 * @brief Frees the memory allocated for a zap_srv_pos_t pointer array and sets
 * it to NULL.
 *
 * This function checks if the given double pointer to zap_srv_pos_t is not
 * NULL, then frees the memory pointed to by the pointer and sets it to NULL to
 * avoid dangling pointers.
 *
 * @param positions Double pointer to a zap_srv_pos_t array to be freed.
 */
static void free_positions(zap_srv_pos_t **positions)
{
    if (!positions || !*positions) {
        return;
    }
    free(*positions);
    *positions = NULL;
}

/**
 * @brief Generates and populates the map with elements based on density.
 *
 * This function initializes and fills the given map structure with elements,
 * distributing them according to computed density values. It performs the
 * following steps:
 *   - Validates the input map and its dimensions.
 *   - Initializes the map if its elements are not already allocated.
 *   - Generates a shuffled list of all possible positions on the map.
 *   - Computes the density table for element distribution.
 *   - Calculates the target number of each element to place on the map.
 *   - Places the elements on the map at randomized positions.
 *
 * @param map Pointer to the zap_srv_map_t structure representing the map to
 * generate.
 */
void generate_map(zap_srv_map_t *map)
{
    ssize_t map_size;
    size_t element_targets[ZAP_SRV_ELEMENTS_QUANTITY] = {0};
    __attribute__((cleanup(free_density)))float *current_density = NULL;
    __attribute__((cleanup(free_positions)))zap_srv_pos_t *positions = NULL;

    if (!map || map->x == 0 || map->y == 0)
        return;
    if (!map->elements)
        init_map(map);
    map_size = map->x * map->y;
    positions = generate_shuffled_positions(map->x, map->y);
    if (!positions || !keep_running(false)) {
        return;
    }
    current_density = compute_density(map);
    if (!current_density || !keep_running(false)) {
        return;
    }
    compute_element_targets(element_targets, current_density, map_size);
    place_elements_on_map(map, positions, element_targets, map_size);
}
