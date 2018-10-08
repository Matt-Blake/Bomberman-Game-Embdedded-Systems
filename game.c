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
        {path, path, path, wall, path, wall, path},
        {wall, path, wall, wall, wall, path, path},
        {path, wall, path, wall, path, wall, path},
        {path, path, wall, path, path, wall, path},
    };
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 7; j++) {
            if(map[i][j] == wall) {
                tinygl_pixel_set(tinygl_point (i, j), wall);
            }
        }
    }

    tinygl_point_t player_location = {0, 0};
    tinygl_pixel_set(player_location, 1);

    while (1) {

        tinygl_update();
        navswitch_update();

        if (navswitch_push_event_p (NAVSWITCH_NORTH) && (player_location.y > 0)) { // modulise all this stuff
            if ((tinygl_pixel_get (tinygl_point (player_location.x, player_location.y - 1))) == 0) {
                tinygl_pixel_set(player_location, 0);
                player_location.y -= 1;
                tinygl_pixel_set(player_location, 1);
            }
        }


        if (navswitch_push_event_p (NAVSWITCH_SOUTH) && (player_location.y < 6)) { // modulise all this stuff and remove constants
            if ((tinygl_pixel_get (tinygl_point (player_location.x, player_location.y + 1))) == 0) {
                tinygl_pixel_set(player_location, 0);
                player_location.y += 1;
                tinygl_pixel_set(player_location, 1);
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_EAST) && (player_location.x < 4)) { // modulise all this stuff and remove constants
            if ((tinygl_pixel_get (tinygl_point (player_location.x + 1, player_location.y))) == 0) {
                tinygl_pixel_set(player_location, 0);
                player_location.x += 1;
                tinygl_pixel_set(player_location, 1);
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_WEST) && (player_location.x > 0)) { // modulise all this stuff and remove constants
            if ((tinygl_pixel_get (tinygl_point (player_location.x - 1, player_location.y))) == 0) {
                tinygl_pixel_set(player_location, 0);
                player_location.x -= 1;
                tinygl_pixel_set(player_location, 1);
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
        tinygl_pixel_set(tinygl_point (player_location.x + 1, player_location.y), path);
            tinygl_pixel_set(tinygl_point (player_location.x - 1, player_location.y), path);
            tinygl_pixel_set(tinygl_point (player_location.x, player_location.y + 1), path);
            tinygl_pixel_set(tinygl_point (player_location.x, player_location.y - 1), path);
        }
    }
}
