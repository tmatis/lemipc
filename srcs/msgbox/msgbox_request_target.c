#include <board.h>
#include <msgbox.h>
#include <errno.h>
#include <ft_logs.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <ft_string.h>

/**
 * @brief Request a target from the team
 * 
 * @param board_instance The board instance
 */
void msgbox_request_target(board_instance_t *board_instance)
{
    msg_t msg = {
        .type = REQUEST_TARGET,
        .team_id_to_broadcast = board_instance->player.team_id,
        .target_id = NO_ID,
    };
    if (msgsnd(board_instance->msg_id, &msg, sizeof(msg), 0) == -1)
    {
        ft_log(
            LOG_LEVEL_FATAL,
            "msgbox_request_target",
            "could not send message: %s",
            ft_strerror(errno));
        exit(EXIT_FAILURE);
    }
}