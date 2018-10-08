#include "system.h"
#include "tinygl.h"

#define wall 1 // remeber to change these to capital
#define path 0

int main (void)
{
    system_init ();
    tinygl_init(50);
    int map[5][7] = {{path, path, wall, wall, path, path, path},
        {path, wall, path, wall, path, wall, path},
        {wall, path, wall, wall, wall, path, path},
        {path, wall, path, wall, path, wall, path},
        {path, path, wall, path, path, wall, path},
    };
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 7; j++) {
            if(map[i][j] == wall) {
                tinygl_pixel_set(tinygl_point (i, j), 1);
            }
        }
    }
    while (1) {
        tinygl_update();
    }
}
