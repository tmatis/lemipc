#pragma once

#include <board.h>
#include <render_utils.h>

/**
 * @brief Convert RGB values to a color
 * 
 */
#define RGB(r, g, b) ((r << 16) + (g << 8) + b)

#define VISUALIZER_WINDOW_WIDTH 1000
#define VISUALIZER_WINDOW_HEIGHT 700
#define VISUALIZER_WINDOW_TITLE "lem-ipc visualizer"

#define VISUALIZER_BOARD_X 25
#define VISUALIZER_BOARD_Y 25
#define VISUALIZER_BOARD_WIDTH 660
#define VISUALIZER_BOARD_HEIGHT 660

#define DARK_GREY RGB(20, 20, 20)

/**
 * @brief Launch the visualizer of the board
 * 
 * @param board_instance The board instance
 */
void visualizer_launch(board_instance_t *board_instance);

void render_board(mlx_t *mlx);

/**
 * @brief Return a RGB color from a team number (random)
 * 
 * @param team_nb The team number
 * @return int The RGB color
 */
int get_team_color(unsigned int team_nb);