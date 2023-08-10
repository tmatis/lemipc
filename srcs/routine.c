#include <routine.h>
#include <ft_logs.h>
#include <msgbox.h>
#include <unistd.h>
#include <pawn.h>

void routine(board_instance_t *board_instance)
{
    int target = -1; // use an algorithm to find a target

    msg_t msg;
    msg.team_id = board_instance->team_id;
    msg.target_id = target;
    msgbox_send(board_instance, &msg);
    while (true)
    {
        board_lock(board_instance);
        if (msgbox_receive(board_instance, &msg))
        {
            ft_log(
                LOG_LEVEL_INFO,
                "routine",
                "received message new target is %d",
                msg.target_id);
            target = msg.target_id;
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
            pawn_leave_board(board_instance);
            break;
        }   
    }
}