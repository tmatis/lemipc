#include <board.h>

size_t board_compute_size(size_t board_size)
{
    int slot_count = board_size * board_size;
    return (sizeof(board_t) + sizeof(int) * slot_count);
}