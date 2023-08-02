#include <render_utils.h>
#include <mlx.h>

/**
 * @brief put a string on a the window
 *
 * @param mlx the mlx ptr
 * @param x x position
 * @param y y position
 * @param color the color
 * @param string the string
 */
void put_string(mlx_t *mlx, int x, int y, int color, char *string)
{
	mlx_string_put(mlx->mlx, mlx->win, x, y, color, string);
}