#include <ft_test.h>
#include <board.h>

START_TEST(board_compute_size, "Test board_compute_size()")
{
    assert_equal(board_compute_size(0), sizeof(board_t));
    assert_equal(board_compute_size(1), sizeof(board_t) + sizeof(int));
    assert_equal(board_compute_size(2), sizeof(board_t) + sizeof(int) * 4);
    assert_equal(board_compute_size(3), sizeof(board_t) + sizeof(int) * 9);
    assert_equal(board_compute_size(4), sizeof(board_t) + sizeof(int) * 16);
    assert_equal(board_compute_size(5), sizeof(board_t) + sizeof(int) * 25);
    assert_equal(board_compute_size(6), sizeof(board_t) + sizeof(int) * 36);
    assert_equal(board_compute_size(7), sizeof(board_t) + sizeof(int) * 49);
    assert_equal(board_compute_size(8), sizeof(board_t) + sizeof(int) * 64);
    assert_equal(board_compute_size(9), sizeof(board_t) + sizeof(int) * 81);
    assert_equal(board_compute_size(10), sizeof(board_t) + sizeof(int) * 100);
} END_TEST