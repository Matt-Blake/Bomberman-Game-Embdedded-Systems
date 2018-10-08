#include "system.h"
#include "tinygl.h"

#define wall 1
#define path 0

int main (void)
{
    system_init ();


    while (1) {

        int map[5][7] = {{wall, wall, wall, wall, wall, wall, wall},
            {wall, path, wall, path, wall, path, wall},
            {wall, path, wall, path, wall, path, wall},
            {wall, path, wall, path, wall, path, wall},
            {wall, path, wall, wall, wall, wall, wall}
        };
        int i = 0;
        int j = 0;
        while(i < 5) {
            while(j < 7) {
                if(map[i][j] == wall) {
                    tinygl_pixel_set(tinygl_point (i, j), 1);
                }
                j += 1;
            }
            i += 1;
        }

    }
}
