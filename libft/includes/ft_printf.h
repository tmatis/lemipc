#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

int ft_printf(const char *format, ...);
int ft_dprintf(int fd, const char *format, ...);
int ft_snprintf(char *dest, size_t size, const char *format, ...);
int ft_asprintf(char **dest, const char *format, ...);

typedef enum {
    PRINTF_WRITE_MODE,
    PRINTF_LEN_MODE,
    PRINTF_BUFFER_MODE
} buffer_mode_t;

typedef struct
{
    char *str;
    size_t len;
    size_t total_len;
    size_t capacity;
    buffer_mode_t mode;
    int fd;
    int error_number;
} printf_buffer_t;

/**
 * @brief Parse the format string
 * 
 * @param format the format string
 * @param args the arguments
 * @param printf_buffer the printf buffer
 */
void printf_wrapper(const char *format, va_list args, printf_buffer_t *printf_buffer);

#endif