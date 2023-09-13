#include <pawn.h>

/**
 * @brief Check if the pawn is dead
 * 
 * @param board_instance the board instance
 * @param x the x position of the pawn
 * @param y the y position of the pawn
 * @return bool_t true if the pawn is dead, false otherwise 
 */
int pawn_count_pawn_around(board_instance_t *board_instance, int x, int y)
{
    int count = 0;
    for (int i = x - 1; i <= x + 1; i++)
    {
        if (i < 0 || i >= board_instance->board->board_size)
            continue;
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (j < 0 || j >= board_instance->board->board_size)
                continue;
            if (i == x && j == y)
                continue;
            if (*pawn_get(board_instance, i, j) != EMPTY_CELL)
                count++;
        }
    }
    return (count);
}