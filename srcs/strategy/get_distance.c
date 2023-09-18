#include <math.h>

/**
 * @brief Get the distance between two points
 * 
 * @param x1 
 * @param y1 
 * @param x2 
 * @param y2 
 * @return double 
 */
double get_distance(int x1, int y1, int x2, int y2)
{
    return fabs(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}