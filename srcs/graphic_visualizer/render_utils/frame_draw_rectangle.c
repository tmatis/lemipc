#include <render_utils.h>

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
void frame_draw_rectangle(frame_t *f, int x, int y, int w, int h, int color)
{
	for (int i = x; i < x + w; i++)
	{
		if (i < 0 || i >= f->x)
			continue;
		for (int j = y; j < y + h; j++)
		{
			if (j < 0 || j >= f->y)
				continue;
			frame_put_pixel(f, i, j, color);
		}
	}
}