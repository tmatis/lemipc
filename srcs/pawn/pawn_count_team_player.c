#include <board.h>

/**
 * @brief Return the number of pawns of a team
 * 
 * @param board_instance the board instance
 * @param team_id the team id
 * @return int the number of pawns of a team
 */
int pawn_count_team_player(board_instance_t *board_instance, int team_id)
{
    int count = 0;
    int board_size = board_instance->board->board_size;
    int *slots = board_instance->board->slots;
    int slot_count = board_size * board_size;

    for (int i = 0; i < slot_count; i++) {
        if (slots[i] == team_id)
            count++;
    }
    return count;
}