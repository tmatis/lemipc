#include <pawn.h>

/**
 * @brief Check if the pawn is dead
 * 
 * @param board_instance the board instance
 * @return bool_t true if the pawn is dead, false otherwise 
 */
int pawn_around_pawn(board_instance_t *board_instance)
{
    int x = board_instance->x;
    int y = board_instance->y;

    int count = 0;
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (i == x && j == y)
                continue;
            if (*pawn_get(board_instance, i, j) != EMPTY_CELL)
                count++;
        }
    }
    return (count);
}