#pragma once

#include <sys/sem.h>
#include <bool_t.h>
#include <stdint.h>

#define EMPTY_CELL -1

#define PLAYER_NO_ID -1

#define IPC_PATH "/tmp/lemipc-tmatis"

#define IPC_KEY 0x0

typedef struct
{
    int player_id;
    int team_id;
} player_t;

typedef struct
{
    int board_size;
    int clients_connected;
    int players_index;
    player_t slots[];
} board_t;

typedef struct
{
    board_t *board;
    int sem_id;
    int shm_id;
    int msg_id;
    int x;
    int y;
    player_t player;
} board_instance_t;

board_instance_t *board_get(bool_t allow_creation, int slot_count);
board_instance_t *board_create(key_t key, int slot_count);
board_instance_t *board_open(key_t key, int slot_count);
void board_lock(board_instance_t *board_instance);
void board_unlock(board_instance_t *board_instance);
void board_disconnect(board_instance_t *board_instance);
size_t board_compute_size(size_t slot_count);