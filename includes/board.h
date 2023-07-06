#pragma once

#include <sys/sem.h>
#include <bool_t.h>
#include <stdint.h>

#define BOARD_SIZE 30
#define EMPTY_CELL -1
#define SLOT_COUNT BOARD_SIZE *BOARD_SIZE

#define PLAYER_NO_ID -1

#define IPC_PATH "/tmp/lemipc-tmatis"

#define IPC_KEY 0x0

typedef struct
{
    int8_t player_id;
    int8_t team_id;
} player_t;

typedef struct
{
    uint8_t clients_connected;
    uint8_t players_index;
    player_t slots[BOARD_SIZE * BOARD_SIZE];
} board_t;

typedef struct
{
    board_t *board;
    int sem_id;
    int shm_id;
    int x;
    int y;
    player_t player;
} board_instance_t;

board_instance_t *board_get(bool_t allow_creation);
board_instance_t *board_create(key_t key);
board_instance_t *board_open(key_t key);
void board_lock(board_instance_t *board_instance);
void board_unlock(board_instance_t *board_instance);
void board_disconnect(board_instance_t *board_instance);