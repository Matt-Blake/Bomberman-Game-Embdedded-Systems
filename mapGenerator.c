#include "system.h"
#include "stdio.h"
#include "tinygl.h"

#define wall 1
#define path 0
#define numRows 15
#define numCols 15

/*
int Map[numCols][numRows] = {{wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall},
    {wall, path, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall},
    {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall},
    {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall},
    {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall},
    {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall},
    {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall},
    {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall},
    {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall},
    {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall},
    {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall},
    {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall},
    {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall},
    {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall},
    {wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall}};
*/

int main(void)
{
    int map[5][7] = {{wall, wall, wall, wall, wall, wall, wall},
        {wall, path, wall, path, wall, path, wall},
        {wall, path, wall, path, wall, path, wall},
        {wall, path, wall, path, wall, path, wall},
        {wall, path, wall, wall, wall, wall, wall}};
    int i = 0;
    int j = 0;
    while(i < 5) {
        while(j < 7) {
            if(map[i][j] == 1) {
                tinygl_pixel_set (tinygl_point_t (i, j), tinygl_pixel_value_t 1;
            }
            j += 1;
        }
        i += 1;
    }
}
