#include <ft_test.h>
#include <board.h>
#include <pawn.h>

START_TEST(test_pawn_get_read, "Test pawn_get() for accessing a pawn on the board")
{
    board_instance_t board_instance;
    board_instance.board = malloc(sizeof(board_t) + sizeof(int) * 10 * 10);
    board_instance.board->board_size = 10;
    for (int i = 0; i < 10 * 10; i++)
        board_instance.board->slots[i] = i;
    assert_equal(*pawn_get(&board_instance, 0, 0), 0);
    assert_equal(*pawn_get(&board_instance, 1, 0), 1);
    assert_equal(*pawn_get(&board_instance, 0, 1), 10);
    free(board_instance.board);
} END_TEST

START_TEST(test_pawn_get_write, "Test pawn_get() for writing a pawn on the board")
{
    board_instance_t board_instance;
    board_instance.board = malloc(sizeof(board_t) + sizeof(int) * 10 * 10);
    board_instance.board->board_size = 10;
    for (int i = 0; i < 10 * 10; i++)
        board_instance.board->slots[i] = i;
    *pawn_get(&board_instance, 0, 0) = 42;
    assert_equal(*pawn_get(&board_instance, 0, 0), 42);
    free(board_instance.board);
} END_TEST