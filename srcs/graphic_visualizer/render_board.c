#include "render_utils.h"
#include <visualizer.h>
#include <pawn.h>

/**
 * @brief Render the pawns on the frame
 * 
 * @param mlx the mlx instance
 */
static void render_pawns(mlx_t *mlx)
{
    int board_size = mlx->board_instance->board->board_size;
    int pawn_size = VISUALIZER_BOARD_WIDTH / board_size;
    for (int x = 0; x < board_size; x++)
    {
        for (int y = 0; y < board_size; y++)
        {
            int pos_x = VISUALIZER_BOARD_X + VISUALIZER_BOARD_WIDTH / board_size * x;
            int pos_y = VISUALIZER_BOARD_Y + VISUALIZER_BOARD_HEIGHT / board_size * y;
            int *cell = pawn_get(mlx->board_instance, x, y);
            if (*cell == EMPTY_CELL)
                continue;
            frame_draw_rectangle(
                &mlx->frame,
                pos_x,
                pos_y,
                pawn_size,
                pawn_size,
                get_team_color(*cell)
            );
        }
    }
}

/**
 * @brief Render the board on the frame
 * 
 * @param mlx the mlx instance
 */
void render_board(mlx_t *mlx)
{
    frame_draw_rectangle(
        &mlx->frame,
        VISUALIZER_BOARD_X,
        VISUALIZER_BOARD_Y,
        VISUALIZER_BOARD_WIDTH,
        VISUALIZER_BOARD_HEIGHT,
        DARK_GREY
    );
    render_pawns(mlx);
}