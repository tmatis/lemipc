#include <ft_logs.h>
#include <ft_printf.h>
#include <ft_colors.h>
#include "../printf/buffer/buffer_printf.h"


static int get_fd_from_level(t_log_level level)
{
    switch (level)
    {
    case LOG_LEVEL_DEBUG:
        return (STDERR_FILENO);
    case LOG_LEVEL_INFO:
        return (STDOUT_FILENO);
    case LOG_LEVEL_WARNING:
        return (STDERR_FILENO);
    case LOG_LEVEL_ERROR:
        return (STDERR_FILENO);
    case LOG_LEVEL_FATAL:
        return (STDERR_FILENO);
    default:
        return (STDERR_FILENO);
    }
}

static const char *get_text_head_from_level(t_log_level level)
{
    switch (level)
    {
    case LOG_LEVEL_DEBUG:
        return (C_BOLD C_MAGENTA_B " DEBUG " C_RESET);
    case LOG_LEVEL_INFO:
        return (C_BOLD C_CYAN_B " INFO " C_RESET);
    case LOG_LEVEL_WARNING:
        return (C_BOLD C_YELLOW_B " WARNING " C_RESET);
    case LOG_LEVEL_ERROR:
        return (C_BOLD C_RED_B " ERROR " C_RESET);
    case LOG_LEVEL_FATAL:
        return (C_BOLD C_RED_B " FATAL " C_RESET);
    default:
        return (C_BOLD C_WHITE_B " UNKNOWN " C_RESET);
    }
}

/**
 * @brief Log a message
 * 
 * @param level The level of the log
 * @param context The context of the log
 * @param message The message to log (printf like)
 * @param ... The arguments to the message
 */
void ft_log(t_log_level level, const char *context, const char *message, ...)
{
    const int fd_to_write = get_fd_from_level(level);
    ft_dprintf(fd_to_write, "%s " C_BOLD "%s" C_RESET ": ", get_text_head_from_level(level), context);
    va_list args;
    va_start(args, message);
    printf_buffer_t printf_buffer = buffer_printf_init(
        PRINTF_WRITE_MODE,
        fd_to_write);
    if (printf_buffer.str == NULL)
        return;
    printf_wrapper(message, args, &printf_buffer);
    va_end(args);
    buffer_printf_destroy(&printf_buffer);
    ft_dprintf(fd_to_write, "%s\n", C_RESET);
}
