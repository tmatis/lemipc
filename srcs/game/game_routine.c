#include <ft_logs.h>
#include <msgbox.h>
#include <unistd.h>
#include <pawn.h>
#include <strategy.h>
#include <unistd.h>
#include <ft_string.h>
#include <utils_lemipc.h>
#include <game.h>

/**
 * @brief Quit the routine and leave the board
 * 
 * @param board_instance 
 */
static void quit_routine(board_instance_t *board_instance)
{
    pawn_leave_board(board_instance);
    board_unlock(board_instance);
}

/**
 * @brief Set the result of the game if not already set
 * 
 * @param board_instance
 * @param result 
 */
static void set_result(board_instance_t *board_instance, int result)
{
    if (board_instance->board->game_result == NO_RESULT)
        board_instance->board->game_result = result;
}

/**
 * @brief Launch the game routine
 * 
 * @param board_instance the board instance
 * @param required_players the number of required players
 * @param speed the speed of the game
 */
void game_routine(
    board_instance_t *board_instance,
    int required_players,
    int speed)
{
    int team_target = -1; // the id of the team we want to attack

    if (game_wait_for_players(board_instance, required_players))
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "could not wait for players, leaving the board");
        board_lock(board_instance);
        pawn_leave_board(board_instance);
        board_unlock(board_instance);
        return;
    }

    while (true)
    {
        int new_target = -1;
        board_lock(board_instance);
        if (force_stop_is_set())
        {
            ft_log(
                LOG_LEVEL_INFO,
                "forced stop, leaving the board");
            quit_routine(board_instance);
            break;
        }
        msg_t msg;
        if (msgbox_receive(board_instance, &msg))
        {
            ft_log(
                LOG_LEVEL_INFO,
                "received message new target is %d",
                msg.target_id);
            new_target = msg.target_id;
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

        if (game_check_is_draw(board_instance))
        {
            set_result(board_instance, DRAW_RESULT);
            quit_routine(board_instance);
            break;
        }
        
        new_target = team_target_result.team_id;
        if (new_target != team_target)
        {
            team_target = new_target;
            ft_log(
                LOG_LEVEL_INFO,
                "new target is %d",
                team_target);
            msg_t msg_to_send;
            ft_memset(&msg_to_send, 0, sizeof(msg_t)); // since there is padding we set everything to 0
            msg_to_send.team_id = board_instance->team_id;
            msg_to_send.target_id = team_target;
            msgbox_send(board_instance, &msg_to_send);
        }
        coord_t next_move = strategy_choose_next_move(
            board_instance,
            &team_target_result);
        pawn_move(board_instance, next_move.x, next_move.y);
        usleep(SLEEP_TIME / (speed * (board_instance->board->players_on_board)));
        board_unlock(board_instance);
    }
}