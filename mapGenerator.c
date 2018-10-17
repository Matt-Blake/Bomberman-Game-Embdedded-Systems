// By Matt Blake: 58979250
// &  James Hay: 78055194
// Group 135


#include "system.h"
#include "tinygl.h"
#include "navswitch.h"

#define wall 1 // remeber to change these to capital
#define path 0

void map_generator_generate(void)
{
    int map[5][7] = {{path, wall, path, wall, path, wall, path}, // map making section
        {path, wall, path, wall, path, wall, path},
        {path, path, wall, wall, wall, path, path},
        {path, wall, path, wall, path, wall, path},
        {path, wall, path, wall, path, wall, path},
    };

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 7; j++) {
            if(map[i][j] == wall) {
                tinygl_pixel_set(tinygl_point (i, j), wall);
            }
        }
    }
}
