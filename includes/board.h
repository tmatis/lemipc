#pragma once

#include <sys/sem.h>
#include <bool_t.h>
#include <stdint.h>

#define EMPTY_CELL -1

#define PLAYER_NO_ID -1

#define IPC_PATH "/tmp/lemipc-tmatis"

#define IPC_KEY 0x0

typedef enum {
    GAME_RUNNING,
    GAME_IDLE,
} game_state_t;

typedef struct
{
    int board_size;
    int clients_connected;
    int players_on_board;
    game_state_t game_state;
    int game_result;
    int slots[];
} board_t;

#define NO_RESULT -1
#define DRAW_RESULT -2

typedef struct
{
    board_t *board;
    int sem_id;
    int shm_id;
    int msg_id;
    int x;
    int y;
    int team_id;
} board_instance_t;

board_instance_t *board_get(bool_t allow_creation, int slot_count);
board_instance_t *board_create(key_t key, int slot_count);
board_instance_t *board_open(key_t key, int slot_count);
void board_lock(board_instance_t *board_instance);
void board_unlock(board_instance_t *board_instance);
void board_disconnect(board_instance_t *board_instance);
size_t board_compute_size(size_t slot_count);