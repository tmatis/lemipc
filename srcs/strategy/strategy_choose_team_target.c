#include <pawn.h>
#include <ft_btree.h>
#include <strategy.h>
#include <ft_logs.h>

typedef struct s_team_coord
{
    int team_id;
    double x;
    double y;
} team_coord_t;

DEFINE_BTREE_HEADERS(team_coord_t);

/**
 * @brief Compare two team coord
 *
 * @param a
 * @param b
 * @return int the difference between the two team id
 */
static int cmp_team_coord(team_coord_t *a, team_coord_t *b)
{
    return a->team_id - b->team_id;
}

DEFINE_BTREE_FUNCTIONS(team_coord_t, cmp_team_coord);

/**
 * @brief Get a map of team coord sorted by team id
 *
 * @param board_instance the board instance
 * @return btree_team_coord_t_node* the map of team coord sorted by team id
 */
static btree_team_coord_t *get_coord_t_map(board_instance_t *board_instance)
{
    btree_team_coord_t *root = NULL;

    for (int x = 0; x < board_instance->board->board_size; x++)
    {
        for (int y = 0; y < board_instance->board->board_size; y++)
        {
            int *team_id = pawn_get(board_instance, x, y);
            if (*team_id == EMPTY_CELL)
                continue;

            team_coord_t team_coord = {
                .team_id = *team_id,
                .x = x,
                .y = y};

            btree_team_coord_t *node =
                btree_team_coord_t_search(root, &team_coord);
            if (!node)
                btree_team_coord_t_insert(&root, &team_coord);
            else
            {
                node->value.x = (node->value.x + x) / 2;
                node->value.y = (node->value.y + y) / 2;
            }
        }
    }
    return root;
}

typedef struct
{
    int team_id;
    int my_team_id;
    double my_team_x;
    double my_team_y;
    double min_distance;
} selector_t;

/**
 * @brief Get the min distance between the team and the other teams
 *
 * @param node the node to check
 */
static void get_min_distance(btree_team_coord_t *node, selector_t *selector)
{
    if (!node)
        return;
    if (node->value.team_id != selector->my_team_id)
    {
        double distance = get_distance(
            node->value.x,
            node->value.y,
            selector->my_team_x,
            selector->my_team_y);
        if (selector->min_distance == -1 || distance < selector->min_distance)
        {
            selector->min_distance = distance;
            selector->team_id = node->value.team_id;
        }
    }
    get_min_distance(node->left, selector);
    get_min_distance(node->right, selector);
}

/**
 * @brief Choose a team to target
 *
 * @param board_instance the board instance
 * @return the team id to target and the coord of my team
 */
team_target_result_t strategy_choose_team_target(board_instance_t *board_instance)
{
    btree_team_coord_t *root = get_coord_t_map(board_instance);

    btree_team_coord_t *my_team_coord = btree_team_coord_t_search(root, &(team_coord_t){.team_id = board_instance->team_id});
    if (!my_team_coord)
        return (team_target_result_t){.team_id = -1};
    selector_t selector = {
        .team_id = -1,
        .my_team_id = board_instance->team_id,
        .my_team_x = my_team_coord->value.x,
        .my_team_y = my_team_coord->value.y,
        .min_distance = -1};
    get_min_distance(root, &selector);
    btree_team_coord_t_clear(&root, NULL);
    return (team_target_result_t){
        .team_id = selector.team_id,
        .my_team_coord = (coord_t){.x = selector.my_team_x, .y = selector.my_team_y}};
}