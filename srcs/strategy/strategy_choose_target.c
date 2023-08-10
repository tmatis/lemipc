#include <pawn.h>
#include <ft_btree.h>
#include <math.h>

typedef struct s_team_coord
{
    int team_id;
    int x;
    int y;
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

    for (int y = 0; y < board_instance->board->board_size; y++)
    {
        for (int x = 0; x < board_instance->board->board_size; x++)
        {
            int *team_id = pawn_get(board_instance, x, y);

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

static int get_distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

static int _min_distance = -1;
static int _team_id = -1;
static int _my_team_id = -1;
static int _my_team_x = -1;
static int _my_team_y = -1;

/**
 * @brief Get the min distance between the team and the other teams
 * 
 * @param node the node to check
 */
static void get_min_distance(btree_team_coord_t *node)
{
    if (!node)
        return;
    if (node->value.team_id != _my_team_id)
    {
        int distance = get_distance(
            node->value.x,
            node->value.y,
            _my_team_x,
            _my_team_y);
        if (_min_distance == -1 || distance < _min_distance)
        {
            _min_distance = distance;
            _team_id = node->value.team_id;
        }
    }
    get_min_distance(node->left);
    get_min_distance(node->right);
}

/**
 * @brief Choose a team to target
 *
 * @param board_instance the board instance
 * @return int the team id to target
 */
int strategy_choose_target(board_instance_t *board_instance)
{
    btree_team_coord_t *root = get_coord_t_map(board_instance);
    btree_team_coord_t *node = root;
    int min_distance = -1;

    btree_team_coord_t *my_team_coord = btree_team_coord_t_search(root, &(team_coord_t){.team_id = board_instance->team_id});
    if (!my_team_coord)
        return -1;
    _my_team_id = my_team_coord->value.team_id;
    _my_team_x = my_team_coord->value.x;
    _my_team_y = my_team_coord->value.y;
    get_min_distance(root);

    int team_id = _team_id;

    _min_distance = -1;
    _team_id = -1;
    _my_team_id = -1;
    _my_team_x = -1;
    _my_team_y = -1;
    btree_team_coord_t_clear(root, NULL);
    return team_id;
}