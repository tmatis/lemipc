#include <board.h>

void pawn_leave_board(board_instance_t *board_instance)
{
    board_lock(board_instance);
    board_instance->board->slots[board_instance->x + board_instance->y * BOARD_SIZE].player_id = EMPTY_CELL;
    board_instance->board->slots[board_instance->x + board_instance->y * BOARD_SIZE].team_id = EMPTY_CELL;
    board_unlock(board_instance);
}