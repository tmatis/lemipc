#include <board.h>
#include <bool_t.h>
#include <ft_logs.h>
#include <stdlib.h>

typedef struct
{
    int8_t x;
    int8_t y;
} coord_t;

/**
 * @brief Find a random free slot on the board
 * 
 * @param board_instance The board instance
 * @return coord_t The coordinates of the free slot
 */
static coord_t find_free_slot(board_instance_t *board_instance)
{
    coord_t coord = {0, 0};

    while (true)
    {
        coord.x = rand() % BOARD_SIZE;
        coord.y = rand() % BOARD_SIZE;
        if (board_instance->board->slots[coord.x + coord.y * BOARD_SIZE].player_id == EMPTY_CELL)
            return (coord);
    }
    /* NOT REACHED */
    return (coord);
}

/**
 * @brief Return true if the pawn has not been placed, false otherwise
 *
 * @param board_instance The board instance
 * @return bool_t true if the pawn has not been placed, false otherwise
 */
bool_t pawn_join_board(board_instance_t *board_instance)
{
    board_lock(board_instance);
    if (board_instance->board->players_index == SLOT_COUNT)
    {
        board_unlock(board_instance);
        ft_log(
            LOG_LEVEL_ERROR,
            "pawn_place",
            "no more slots available");
        return (true);
    }

    coord_t coord = find_free_slot(board_instance);
    board_instance->x = coord.x;
    board_instance->y = coord.y;
    player_t *slot = &board_instance->board->slots[coord.x + coord.y * BOARD_SIZE];
    
    slot->player_id = ++board_instance->board->players_index;
    slot->team_id = board_instance->player.team_id;

    
}