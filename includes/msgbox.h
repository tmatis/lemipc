#pragma once

typedef struct
{
    long team_id;
    int target_id;
} msg_t;

/**
 * @brief Receive a message from the message box
 * 
 * @param board_instance the board instance
 * @param msg the message pointer to fill
 * @return bool_t true if a message was received, false otherwise
 */
bool_t msgbox_receive(board_instance_t *board_instance, msg_t *msg);

/**
 * @brief Send a message to the message box
 * 
 * @param board_instance the board instance
 * @param msg the message to send
 * @return bool_t true if the message was sent, false otherwise
 */
bool_t msgbox_send(board_instance_t *board_instance, msg_t *msg);