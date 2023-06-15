#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <ft_printf.h>
#include <sys/sem.h>
#include <ft_string.h>
#include <ft_logs.h>
#include <errno.h>

#define MAP_SIZE 100
#define SHM_KEY_PATH "/tmp/"
#define SHM_KEY_ID 0x42
#define SEM_KEY_PATH "/tmp"
#define SEM_KEY_ID 0x43

typedef struct {
	size_t size;
	int board[MAP_SIZE * MAP_SIZE];
} board_t;


int main(void)
{
	key_t key = ftok(SHM_KEY_PATH, SHM_KEY_ID);
	if (key == -1)
	{
		ft_log(
			LOG_LEVEL_FATAL,
			"main",
			"could not get key " C_BOLD "(%s:%#x)" C_RESET ": %s",
			SHM_KEY_PATH,
			SHM_KEY_ID,
			ft_strerror(errno));
		return (1);
	}
	int shm_id = shmget(key, sizeof(board_t), 0666);
	if (shm_id == -1)
	{
		ft_log(LOG_LEVEL_INFO, "main", "shmget not yet initialized");
		shm_id = shmget(key, sizeof(board_t), IPC_CREAT | 0666);
	}
	board_t *board = shmat(shm_id, NULL, 0);
	if (board == (void *)-1)
	{
		ft_log(LOG_LEVEL_FATAL, "main", "shmat failed: %s", ft_strerror(errno));
		return (1);
	}

	key_t sem_key = ftok(SEM_KEY_PATH, SEM_KEY_ID);
	if (sem_key == -1)
	{
		ft_dprintf(2, "Error: ftok failed\n");
		return (1);
	}
	int sem_id = semget(sem_key, 1, IPC_CREAT | 0666);
	if (sem_id == -1)
	{
		ft_dprintf(2, "Error: semget failed\n");
		return (1);
	}
	// get value of semaphore
	struct sembuf sops;
	sops.sem_num = 0;
	sops.sem_op = 0;
	sops.sem_flg = 0;
	if (semop(sem_id, &sops, 1) == -1)
	{
		ft_dprintf(2, "Error: semop failed\n");
		return (1);
	}



	board->size = MAP_SIZE;
	for (size_t i = 0; i < MAP_SIZE * MAP_SIZE; i++)
		board->board[i] = 0;
	shmdt(board);
	// destroy the shared memory
	// shmctl(shm_id, IPC_RMID, NULL);
	return (0);
}