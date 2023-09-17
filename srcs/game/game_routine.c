#include <ft_logs.h>
#include <msgbox.h>
#include <unistd.h>
#include <pawn.h>
#include <strategy.h>
#include <game.h>
#include <unistd.h>
#include <ft_string.h>

static void quit_routine(board_instance_t *board_instance)
{
    pawn_leave_board(board_instance);
    board_unlock(board_instance);
}

static bool_t can_start(board_instance_t *board_instance, int required_players)
{
    board_lock(board_instance);
    if (board_instance->board->players_on_board >= required_players)
    {
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
    {
        usleep(100000);
    }
    ft_log(
        LOG_LEVEL_INFO,
        "game start semaphore unlocked");
    game_start_unlock(board_instance);
}

void game_routine(board_instance_t *board_instance, int required_players)
{
    int team_target = -1; // the id of the team we want to attack

    wait_for_players(board_instance, required_players);

    // char c;
    // read(STDIN_FILENO, &c, 1);

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

        if (board_instance->board->players_on_board <= 2)
        {
            ft_log(
                LOG_LEVEL_INFO,
                "There is less than 3 players connected, leaving the board");
            quit_routine(board_instance);
            break;
        }

        team_target_result_t team_target_result = strategy_choose_team_target(board_instance);
        if (team_target_result.team_id == -1)
        {
            ft_log(
                LOG_LEVEL_INFO,
                "No more target to attack, I'm leaving the board");
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