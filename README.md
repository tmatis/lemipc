# Lem-ipc

![image](https://github.com/tmatis/lemipc/assets/54767855/179a7162-1d6e-4ab3-a745-bafe23dfa21d)

## Description

Lem-ipc is a project where you have to implement a communication system between processes using shared memory, semaphores and message queues.

## Usage

### Build the project

```bash
make
```

> This will build the project and create the executable `lemipc` and `lemipc_visualizer`

### build with debug symbols

```bash
make debug
```

> This will build the project with debug symbols and create the executable `lemipc_debug` and `lemipc_visualizer_debug`

### Run the project

```bash
./lemipc arena_size team_nb minimum_players [speed]
```

#### Project parameters

- `arena_size`: The size of the arena
- `team_nb`: The id of the team
- `minimum_players`: The minimum number of players to start the game
- `speed`: The speed of the game (optional)

### Run the visualizer

```bash
./lemipc_visualizer arena_size
```

#### Visualizer parameters

- `arena_size`: The size of the arena
