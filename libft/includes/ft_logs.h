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
 * @param file_name The file name of the log
 * @param line The line of the log
 * @param function_name The level of the log
 * @param message The message to log (printf like)
 * @param ... The arguments to the message
 */
void _ft_log(t_log_level level, const char *file_name, int line, const char *function_name, const char *message, ...);

/**
 * @brief Log a message
 * 
 * @param level The level of the log
 * @param ... The arguments to the message
 */
#define ft_log(level, ...) _ft_log(level, __FILE__, __LINE__, __func__, __VA_ARGS__)

#endif