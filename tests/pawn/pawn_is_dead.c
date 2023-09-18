#include <ft_test.h>
#include <board.h>
#include <pawn.h>

START_TEST(pawn_is_dead_not_dead, "Test pawn_is_dead() when no pawn around")
{
    board_instance_t board_instance;
    board_instance.board = malloc(sizeof(board_t) + sizeof(int) * 10 * 10);
    board_instance.board->board_size = 10;
    board_instance.x = 0;
    board_instance.y = 0;
    for (int i = 0; i < 10 * 10; i++)
        board_instance.board->slots[i] = PLAYER_NO_ID;
    assert_equal(pawn_is_dead(&board_instance), false);
    free(board_instance.board);
} END_TEST

START_TEST(pawn_is_dead_dead, "Test pawn_is_dead() when a pawn is around")
{
    board_instance_t board_instance;
    board_instance.board = malloc(sizeof(board_t) + sizeof(int) * 10 * 10);
    board_instance.board->board_size = 10;
    board_instance.x = 0;
    board_instance.y = 0;
    for (int i = 0; i < 10 * 10; i++)
        board_instance.board->slots[i] = PLAYER_NO_ID;
    *pawn_get(&board_instance, 0, 1) = 1;
    assert_equal(pawn_is_dead(&board_instance), false);
    free(board_instance.board);
} END_TEST

START_TEST(pawn_is_dead_dead_2, "Test pawn_is_dead() when 2 pawn is around")
{
    board_instance_t board_instance;
    board_instance.board = malloc(sizeof(board_t) + sizeof(int) * 10 * 10);
    board_instance.board->board_size = 10;
    board_instance.x = 0;
    board_instance.y = 0;
    for (int i = 0; i < 10 * 10; i++)
        board_instance.board->slots[i] = PLAYER_NO_ID;
    *pawn_get(&board_instance, 1, 0) = 1;
    *pawn_get(&board_instance, 1, 1) = 1;
    assert_equal(pawn_is_dead(&board_instance), true);
    free(board_instance.board);
} END_TEST

