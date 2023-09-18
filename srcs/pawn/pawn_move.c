#include <ft_logs.h>
#include <pawn.h>

/**
 * @brief Move a pawn to a new position while checking if the move is valid
 * 
 * @param board_instance
 * @param x 
 * @param y 
 */
void pawn_move(board_instance_t *board_instance, int x, int y)
{
    int *pawn = pawn_get(board_instance, board_instance->x, board_instance->y);
    if (*pawn == EMPTY_CELL)
    {
        ft_log(LOG_LEVEL_ERROR, "pawn is empty");
        return;
    }

    if (x < 0 || x >= board_instance->board->board_size)
    {
        ft_log(LOG_LEVEL_ERROR, "x is out of bounds");
        return;
    }
    if (y < 0 || y >= board_instance->board->board_size)
    {
        ft_log(LOG_LEVEL_ERROR, "y is out of bounds");
        return;
    }
    // pawn can only move one cell at a time diagonally or orthogonally
    if (x < board_instance->x - 1 || x > board_instance->x + 1)
    {
        ft_log(LOG_LEVEL_ERROR, "x is too far");
        return;
    }
    if (y < board_instance->y - 1 || y > board_instance->y + 1)
    {
        ft_log(LOG_LEVEL_ERROR, "y is too far");
        return;
    }
    int *target_pawn = pawn_get(board_instance, x, y);
    if (*target_pawn != EMPTY_CELL)
    {
        ft_log(LOG_LEVEL_ERROR, "target pawn is not empty");
        return;
    }
    *target_pawn = *pawn;
    *pawn = EMPTY_CELL;
    board_instance->x = x;
    board_instance->y = y;
}