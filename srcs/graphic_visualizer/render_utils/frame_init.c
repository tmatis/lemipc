#include <errno.h>
#include <mlx.h>
#include <stdlib.h>
#include <ft_logs.h>
#include <ft_string.h>
#include <render_utils.h>

/**
 * @brief Frame constructor
 * 
 * @param mlx the mlx ptr
 * @param x the x position of the frame
 * @param y the y position of the frame
 * @return frame_t 
 */
frame_t	frame_init(void *mlx, int x, int y)
{
	frame_t	frame;

	frame.img = mlx_new_image(mlx, x, y);
	if (!frame.img)
	{
		ft_log(
            LOG_LEVEL_FATAL,
            "frame_init",
            "mlx_new_image failed: %s",
            ft_strerror(errno)
        );
        exit(EXIT_FAILURE);
	}
	frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel,
			&frame.line_length, &frame.endian);
	if (!frame.addr)
	{
		ft_log(
            LOG_LEVEL_FATAL,
            "frame_init",
            "mlx_get_data_addr failed: %s",
            ft_strerror(errno)
        );
        exit(EXIT_FAILURE);
	}
	frame.x = x;
	frame.y = y;
	return (frame);
}
