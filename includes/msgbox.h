#pragma once

#define NO_ID -1

typedef enum {
    REQUEST_TARGET,
    BROADCAST_TARGET,
} msgtype_t;

typedef struct {
    msgtype_t type;
    int target_id; // NO_ID for REQUEST_TARGET
    int team_id_to_broadcast;
} msg_t;

