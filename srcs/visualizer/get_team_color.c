#include <stdlib.h>
#include <stdio.h>
#include <visualizer.h>

static const int color_by_team[] = {
    RGB(255, 0, 0),
    RGB(0, 255, 0),
    RGB(0, 0, 255),
    RGB(255, 255, 0),
    RGB(255, 0, 255),
    RGB(0, 255, 255),
    RGB(128, 128, 128),
    RGB(128, 0, 0),
    RGB(0, 128, 0),
    RGB(0, 0, 128),
    RGB(128, 128, 0),
    RGB(128, 0, 128),
    RGB(0, 128, 128),
    RGB(192, 192, 192),
    RGB(192, 0, 0),
    RGB(0, 192, 0),
    RGB(0, 0, 192),
    RGB(192, 192, 0),
    RGB(192, 0, 192),
    RGB(0, 192, 192),
};

/**
 * @brief Return a RGB color from a team number
 * 
 * @param team_nb The team number
 * @return int The RGB color
 */
int get_team_color(unsigned int team_nb)
{
    if (sizeof(color_by_team) / sizeof(int) > team_nb)
        return (color_by_team[team_nb]);

    int r = (team_nb * 10) % 255;
    int g = (team_nb * 20) % 255;
    int b = (team_nb * 30) % 255;

    return (r << 16) + (g << 8) + b;
}