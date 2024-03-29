#include <board.h>
#include <msgbox.h>
#include <errno.h>
#include <ft_logs.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <ft_string.h>

/**
 * @brief Receive a message from the message box
 * 
 * @param board_instance the board instance
 * @param msg the message pointer to fill
 * @return bool_t true if a message was received, false otherwise
 */
bool_t msgbox_receive(board_instance_t *board_instance, msg_t *msg)
{
    int team_id = board_instance->team_id;
    int msgbox_id = board_instance->msg_id;
    if (msgrcv(msgbox_id, msg, sizeof(msg_t) - sizeof(long), team_id, IPC_NOWAIT) != -1)
    { 
        ft_log(
            LOG_LEVEL_DEBUG,
            "received message from team %d",
            msg->team_id);
        return (true);
    }
    if (errno != ENOMSG && errno != EAGAIN)
        ft_log(LOG_LEVEL_WARNING, "msgrcv failed %s", ft_strerror(errno));
    return (false);
}