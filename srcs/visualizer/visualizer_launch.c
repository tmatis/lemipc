#include <board.h>
#include <mlx.h>
#include <stdlib.h>
#include <visualizer.h>
#include <ft_printf.h>
#include "render_utils.h"

/**
 * @brief Callback called when the window is closed
 * 
 * @param mlx_ptr The mlx pointer
 * @return int The return value (always 0)
 */
static int on_close(void *mlx_ptr)
{
    mlx_loop_end(mlx_ptr);
    return (0);
}


static void text_rendering(mlx_t *mlx)
{
    char *client_connected_text;

    ft_asprintf(
        &client_connected_text,
        "Client connected: %i",
        mlx->board_instance->board->clients_connected
    );

    if (!client_connected_text)
        return ;

    put_string(
        mlx,
        700,
        40,
        RGB(255, 255, 255),
        client_connected_text
    );
    free(client_connected_text);
}

static void graphic_rendering(mlx_t *mlx)
{
    render_board(mlx);
}

static int render(mlx_t *mlx)
{
    board_lock(mlx->board_instance);
    frame_draw_rectangle(
        &mlx->frame,
        0,
        0,
        VISUALIZER_WINDOW_WIDTH,
        VISUALIZER_WINDOW_HEIGHT,
        RGB(0, 0, 0)
    );
    graphic_rendering(mlx);
    mlx_put_image_to_window(
        mlx->mlx,
        mlx->win,
        mlx->frame.img,
        0,
        0
    );
    text_rendering(mlx);
    board_unlock(mlx->board_instance);
    return (0);
}

/**
 * @brief Launch the visualizer of the board
 *
 * @param board_instance The board instance
 */
void visualizer_launch(board_instance_t *board_instance)
{
    (void)board_instance;
    void *mlx_ptr = mlx_init();
    void *win_ptr = mlx_new_window(
        mlx_ptr,
        VISUALIZER_WINDOW_WIDTH,
        VISUALIZER_WINDOW_HEIGHT,
        VISUALIZER_WINDOW_TITLE);
    frame_t frame = frame_init(mlx_ptr, VISUALIZER_WINDOW_WIDTH, VISUALIZER_WINDOW_HEIGHT);
    mlx_t mlx = {
        .board_instance = board_instance,
        .mlx = mlx_ptr,
        .win = win_ptr,
        .frame = frame
    };
    mlx_hook(win_ptr, 17, 0, on_close, mlx_ptr);
    mlx_loop_hook(mlx_ptr, render, &mlx);
    mlx_loop(mlx_ptr);
    mlx_destroy_window(mlx_ptr, win_ptr);
    mlx_destroy_display(mlx_ptr);
    free(mlx_ptr);
}