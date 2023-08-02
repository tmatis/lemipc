#include <board.h>

size_t board_compute_size(size_t slot_count)
{
    return (sizeof(board_t) + sizeof(player_t) * slot_count * slot_count);
}