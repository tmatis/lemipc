#include <board.h>
#include <msgbox.h>
#include <errno.h>
#include <ft_logs.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <ft_string.h>
#include <pawn.h>

/**
 * @brief Send a message to the message box
 * 
 * @param board_instance the board instance
 * @param msg the message to send
 * @return bool_t true if the message was sent, false otherwise
 */
bool_t msgbox_send(board_instance_t *board_instance, msg_t *msg)
{
    int msgbox_id = board_instance->msg_id;
    int team_count = pawn_count_team_player(board_instance, msg->team_id);

    while (team_count--)
    {
        if (msgsnd(msgbox_id, msg, sizeof(msg_t) - sizeof(long), 0) == -1)
        {
            ft_log(LOG_LEVEL_WARNING, "msgsnd failed %s", ft_strerror(errno));
            return (false);
        }
    }
    ft_log(
        LOG_LEVEL_DEBUG,
        "sent message to team %d",
        msg->team_id);
    return (true);
}