#include <routine.h>
#include <ft_logs.h>
#include <msgbox.h>

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
			// do something with the message
		}
		else
			ft_log(LOG_LEVEL_INFO, "routine", "no message received");
		usleep(1000000);
		board_unlock(board_instance);
	}
	hang();
}