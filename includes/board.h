#pragma once

#include <sys/sem.h>

#define BOARD_SIZE 30
#define EMPTY_CELL -1


#define IPC_PATH "/tmp/lemipc-tmatis"

#define IPC_KEY 0x0

typedef struct {
    int players_count;
    int slots[BOARD_SIZE * BOARD_SIZE];
} board_t;

typedef struct {
    board_t *board;
    int sem_id;
    int player_id;
} board_instance_t;

board_instance_t *board_get(void);
board_instance_t *board_create(key_t key);
board_instance_t *board_open(key_t key);
void board_lock(board_instance_t *board_instance);
void board_unlock(board_instance_t *board_instance);