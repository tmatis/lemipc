#include <render_utils.h>

/**
 * @brief Put a pixel on a frame and check boundaries
 *
 * @param f the frame ptr
 * @param x x position
 * @param y y position
 * @param color the color
 */
void frame_put_pixel(frame_t *f, int x, int y, int color)
{
	if (x <= f->x && y <= f->y && x >= 0 && y >= 0)
	{
		char *dst;

		dst = f->addr + (y * f->line_length + x * (f->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}