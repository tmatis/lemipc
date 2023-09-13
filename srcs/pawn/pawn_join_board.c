#include <board.h>
#include <bool_t.h>
#include <ft_logs.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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
    srand(time(NULL));

    int board_size = board_instance->board->board_size;

    while (true)
    {
        coord.x = rand() % board_size;
        coord.y = rand() % board_size;
        if (board_instance->board->slots[coord.x + coord.y * board_size] == EMPTY_CELL)
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
    int board_size = board_instance->board->board_size;
    if (board_instance->board->players_on_board == board_size * board_size)
    {
        board_unlock(board_instance);
        ft_log(
            LOG_LEVEL_ERROR,
            "pawn_join_board",
            "no more slots available");
        return true;
    }

    coord_t coord = find_free_slot(board_instance);
    board_instance->x = coord.x;
    board_instance->y = coord.y;
    int *slot = &board_instance->board->slots[coord.x + coord.y * board_size];

    board_instance->board->players_on_board++;
    *slot = board_instance->team_id;
    board_unlock(board_instance);
    return false;
}