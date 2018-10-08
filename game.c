#include "system.h"
#include "tinygl.h"
#include "navswitch.h"

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

    tinygl_point_t player_location = {1, 1};
    tinygl_pixel_set(player_location, 1);

    while (1) {

        tinygl_update();
        navswitch_update();

        if (navswitch_push_event_p (NAVSWITCH_NORTH)) { // modulise all this stuff
            tinygl_pixel_set(player_location, 0);
            player_location.y += 1;
            tinygl_pixel_set(player_location, 1);
        }


        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            tinygl_pixel_set(player_location, 0);
            player_location.y -= 1;
            tinygl_pixel_set(player_location, 1);
        }

        if (navswitch_push_event_p (NAVSWITCH_EAST)) {
            tinygl_pixel_set(player_location, 0);
            player_location.x += 1;
            tinygl_pixel_set(player_location, 1);
        }

        if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            tinygl_pixel_set(player_location, 0);
            player_location.x -= 1;
            tinygl_pixel_set(player_location, 1);
        }
    }
}
