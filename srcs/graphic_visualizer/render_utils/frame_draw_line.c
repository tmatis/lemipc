#include <render_utils.h>

/**
 * @brief return sign of a number
 *
 * @param x the number
 * @return int 0, 1 or -1
 */
static int sign(int x)
{
	if (x > 0)
		return 1;
	else if (x < 0)
		return -1;
	else
		return 0;
}

/**
 * @brief return the absolute value of a number
 *
 * @param x the number
 * @return int the absolute value
 */
static int ft_abs(int x)
{
	if (x < 0)
		return -x;
	return x;
}

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
void frame_draw_line(frame_t *f, int x1, int y1, int x2, int y2, int color)
{
	int x, y, dx, dy, swap, s1, s2, p, i;

	x = x1;
	y = y1;
	dx = ft_abs(x2 - x1);
	dy = ft_abs(y2 - y1);
	s1 = sign(x2 - x1);
	s2 = sign(y2 - y1);
	swap = 0;

	if (dy > dx)
	{
		
		int temp = dx;
		dx = dy;
		dy = temp;
		swap = 1;
	}
	p = 2 * dy - dx;
	for (i = 0; i < dx; i++)
	{
		frame_put_pixel(f, x, y, color);
		while (p >= 0)
		{
			p = p - 2 * dx;
			if (swap)
				x += s1;
			else
				y += s2;
		}
		p = p + 2 * dy;
		if (swap)
			y += s2;
		else
			x += s1;
	}
	frame_put_pixel(f, x2, y2, color);
}