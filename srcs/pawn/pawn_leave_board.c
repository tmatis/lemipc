#include <board.h>

void pawn_leave_board(board_instance_t *board_instance)
{
    board_lock(board_instance);
    int board_size = board_instance->board->board_size;
    board_instance->board->slots[board_instance->x + board_instance->y * board_size].player_id = EMPTY_CELL;
    board_instance->board->slots[board_instance->x + board_instance->y * board_size].team_id = EMPTY_CELL;
    board_unlock(board_instance);
}