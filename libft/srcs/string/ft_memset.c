#include <ft_string.h>

/**
 * @brief Set bytes in memory
 * 
 * @param s the memory area to set
 * @param c the byte to set
 * @param n the number of bytes to set
 * @return void* a pointer to the memory area
 */
void *ft_memset(void *s, int c, size_t n)
{
    unsigned char *ptr = s;
    while (n--)
        *ptr++ = (unsigned char)c;
    return (s);
}