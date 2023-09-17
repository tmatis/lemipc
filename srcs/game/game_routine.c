#include <ft_logs.h>
#include <msgbox.h>
#include <unistd.h>
#include <pawn.h>
#include <strategy.h>
#include <game.h>
#include <unistd.h>
#include <ft_string.h>
#include <int_map.h>

static void quit_routine(board_instance_t *board_instance)
{
    pawn_leave_board(board_instance);
    board_unlock(board_instance);
}

static bool_t can_start(board_instance_t *board_instance, int required_players)
{
    board_lock(board_instance);
    if (board_instance->board->game_state == GAME_RUNNING)
    {
        board_unlock(board_instance);
        return true;
    }
    board_instance->board->game_result = NO_RESULT;
    if (board_instance->board->players_on_board >= required_players)
    {
        board_instance->board->game_state = GAME_RUNNING;
        board_unlock(board_instance);
        return true;
    }
    board_unlock(board_instance);
    return false;
}

static void wait_for_players(board_instance_t *board_instance, int required_players)
{
    ft_log(
        LOG_LEVEL_INFO,
        "waiting for %d players",
        required_players);
    game_start_lock(board_instance);
    ft_log(
        LOG_LEVEL_INFO,
        "game start semaphore locked");
    while (!can_start(board_instance, required_players))
        usleep(100000);
    ft_log(
        LOG_LEVEL_INFO,
        "game start semaphore unlocked");
    game_start_unlock(board_instance);
}

static bool_t check_is_draw(board_instance_t *board_instance)
{
    btree_int_map_t *root = NULL;
    int board_size = board_instance->board->board_size;
    for (int i = 0; i < board_size * board_size; i++)
    {
        int slot = board_instance->board->slots[i];
        if (slot == EMPTY_CELL)
            continue;
        int_map_t int_map = {slot, 1};
        btree_int_map_t *node = btree_int_map_t_search(root, &int_map);
        if (node == NULL)
            btree_int_map_t_insert(&root, &int_map);
        else
        {
            btree_int_map_t_clear(&root, NULL);
            return false;
        }
    }
    btree_int_map_t_clear(&root, NULL);
    return true;
}

static void set_result(board_instance_t *board_instance, int result)
{
    if (board_instance->board->game_result == NO_RESULT)
        board_instance->board->game_result = result;
}

void game_routine(board_instance_t *board_instance, int required_players)
{
    int team_target = -1; // the id of the team we want to attack

    wait_for_players(board_instance, required_players);

    while (true)
    {
        msg_t msg;
        board_lock(board_instance);
        if (msgbox_receive(board_instance, &msg))
        {
            ft_log(
                LOG_LEVEL_INFO,
                "received message new target is %d",
                msg.target_id);
            team_target = msg.target_id;
        }
        if (pawn_is_dead(board_instance))
        {
            ft_log(
                LOG_LEVEL_INFO,
                "surrounded by 2 pawn from the same team, leaving the board");
            quit_routine(board_instance);
            break;
        }

        team_target_result_t team_target_result = strategy_choose_team_target(board_instance);
        if (team_target_result.team_id == -1)
        {
            set_result(board_instance, board_instance->team_id);
            quit_routine(board_instance);
            break;
        }

        if (check_is_draw(board_instance))
        {
            set_result(board_instance, DRAW_RESULT);
            quit_routine(board_instance);
            break;
        }

        if (team_target_result.team_id != team_target)
        {
            team_target = team_target_result.team_id;
            ft_log(
                LOG_LEVEL_INFO,
                "new target is %d",
                team_target);
            msg_t msg;
            ft_memset(&msg, 0, sizeof(msg_t)); // since there is padding we set everything to 0
            msg.team_id = board_instance->team_id;
            msg.target_id = team_target;
            msgbox_send(board_instance, &msg);
        }
        coord_t next_move = strategy_choose_next_move(
            board_instance,
            &team_target_result);
        pawn_move(board_instance, next_move.x, next_move.y);
        usleep(250000);
        board_unlock(board_instance);
    }
}