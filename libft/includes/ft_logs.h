#ifndef FT_LOGS_H
# define FT_LOGS_H

#include "ft_colors.h"


typedef enum e_log_level
{
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
} t_log_level;

/**
 * @brief Log a message
 * 
 * @param level The level of the log
 * @param context The context of the log
 * @param message The message to log (printf like)
 * @param ... The arguments to the message
 */
void ft_log(t_log_level level, const char *context, const char *message, ...);

#endif