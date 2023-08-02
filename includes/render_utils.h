#pragma once

#include <board.h>

/**
 * @brief The frame struct
 * 
 */
typedef struct s_frame
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int x;
	int y;
} frame_t;

typedef struct s_mlx
{
	void *mlx;
	void *win;
	frame_t frame;
    board_instance_t *board_instance;
} mlx_t;

/**
 * @brief Put a pixel on a frame and check boundaries
 *
 * @param f the frame ptr
 * @param x x position
 * @param y y position
 * @param color the color
 */
void frame_put_pixel(frame_t *f, int x, int y, int color);

/**
 * @brief Draw a line using Bresenham algorithm
 *
 * @param f the frame ptr
 * @param x1 x position of the first point
 * @param y1 y position of the first point
 * @param x2 x position of the second point
 * @param y2 y position of the second point
 * @param color the color
 */
void frame_draw_line(frame_t *f, int x1, int y1, int x2, int y2, int color);

/**
 * @brief Draw a rectangle on a frame
 *
 * @param f the frame ptr
 * @param x x position
 * @param y y position
 * @param w width
 * @param h height
 * @param color
 */
void frame_draw_rectangle(frame_t *f, int x, int y, int w, int h, int color);

/**
 * @brief Frame constructor
 * 
 * @param mlx the mlx ptr
 * @param x the x position of the frame
 * @param y the y position of the frame
 * @return frame_t 
 */
frame_t	frame_init(void *mlx, int x, int y);

/**
 * @brief put a string on a the window
 *
 * @param mlx the mlx ptr
 * @param x x position
 * @param y y position
 * @param color the color
 * @param string the string
 */
void put_string(mlx_t *mlx, int x, int y, int color, char *string);