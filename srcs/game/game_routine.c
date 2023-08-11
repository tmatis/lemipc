#include <ft_logs.h>
#include <msgbox.h>
#include <unistd.h>
#include <pawn.h>
#include <strategy.h>
#include <game.h>
#include <unistd.h>

static void quit_routine(board_instance_t *board_instance)
{
    pawn_leave_board(board_instance);
    board_unlock(board_instance);
}

static bool_t can_start(board_instance_t *board_instance, int required_players)
{
    board_lock(board_instance);
    if (board_instance->board->players_index >= required_players)
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
        "wait_for_players",
        "waiting for %d players",
        required_players);
    game_start_lock(board_instance);
    ft_log(
        LOG_LEVEL_INFO,
        "wait_for_players",
        "game start semaphore locked");
    while (!can_start(board_instance, required_players))
    {
        ft_log(
            LOG_LEVEL_INFO,
            "wait_for_players",
            "waiting for players");
        usleep(10000);
    }
    game_start_unlock(board_instance);
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
                "routine",
                "received message new target is %d",
                msg.target_id);
            team_target = msg.target_id;
        }
        int x = board_instance->x;
        int y = board_instance->y;
        int pawn_around_count = pawn_count_pawn_around(board_instance, x, y);
        if (pawn_around_count == 2)
        {
            ft_log(
                LOG_LEVEL_INFO,
                "routine",
                "Oh no! I'm surrounded by 2 pawn ! I'm dead!");
            quit_routine(board_instance);
            break;
        }

        int potential_team_target = strategy_choose_target(board_instance);
        if (potential_team_target == -1)
        {
            ft_log(
                LOG_LEVEL_INFO,
                "routine",
                "No more target to attack, I'm leaving the board");
            quit_routine(board_instance);
            break;
        }
        if (potential_team_target != team_target)
        {
            ft_log(
                LOG_LEVEL_INFO,
                "routine",
                "new target is %d",
                potential_team_target);
            team_target = potential_team_target;
            msgbox_send(
                board_instance,
                &(msg_t){
                    .team_id = board_instance->team_id,
                    .target_id = team_target,
                });
        }
        board_unlock(board_instance);
    }
}