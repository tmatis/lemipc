#include <board.h>

/**
 * @brief Leave the board and update counters and game state
 * 
 * @param board_instance 
 */
void pawn_leave_board(board_instance_t *board_instance)
{
    int board_size = board_instance->board->board_size;
    board_instance->board->slots[board_instance->x + board_instance->y * board_size] = EMPTY_CELL;
    board_instance->board->players_on_board--;
    if (board_instance->board->players_on_board == 0)
        board_instance->board->game_state = GAME_IDLE;
}