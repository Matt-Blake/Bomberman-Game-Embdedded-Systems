#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"
#include "pacer.h"

#define wall 1 // remeber to change these to capital
#define path 0

int main (void)
{
    system_init ();
    pacer_init (500);
    tinygl_init (500); // #define this
    ir_uart_init ();
    tinygl_text_speed_set (20);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_font_set (&font5x7_1);

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

    tinygl_point_t player_location = {0, 0}; // fix variable names
    tinygl_pixel_set(player_location, 1);
    tinygl_point_t bomb_location = {0, 0};

    int timesThroughLoop = 0;
    int timeForBomb = 0;
    int bomb_dropped = 0;
    int win = 0;
    while (1) {

        if (ir_uart_read_ready_p ()) { // Is this right.
            //char ch;

            //ch = ir_uart_getc ();
        }

        tinygl_update();
        navswitch_update();

        if(timesThroughLoop == 1000) { // Flashes the Player
            tinygl_pixel_set(player_location, 0);
        } else if(timesThroughLoop == 2000) {
            tinygl_pixel_set(player_location, 1);
            timesThroughLoop = 0;
        }

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
            bomb_dropped = 1;
            timeForBomb = 0;
            bomb_location.x = player_location.x;
            bomb_location.y = player_location.y;

        }

        if(((timeForBomb % 200) == 0 && (bomb_dropped == 1))) {
            tinygl_pixel_set(bomb_location, 0);
        } else if(((timeForBomb % 100) == 0) && (bomb_dropped == 1)) {
            tinygl_pixel_set(bomb_location, 1);
        }

        if ((timeForBomb == 3000) && (bomb_dropped == 1)) {
            tinygl_pixel_set(tinygl_point (bomb_location.x + 1, bomb_location.y), path); // neaten all this up
            tinygl_pixel_set(tinygl_point (bomb_location.x - 1, bomb_location.y), path);
            tinygl_pixel_set(tinygl_point (bomb_location.x, bomb_location.y + 1), path);
            tinygl_pixel_set(tinygl_point (bomb_location.x, bomb_location.y - 1), path);
            tinygl_pixel_set(bomb_location, 0);
            timeForBomb = 0;
            bomb_dropped = 0;
            if (((player_location.x == bomb_location.x) && ((player_location.y == bomb_location.y) || (player_location.y == (bomb_location.y - 1)) || (player_location.y == (bomb_location.y + 1)))) || ((player_location.y == bomb_location.y) && ((player_location.x == bomb_location.x) || (player_location.x == (bomb_location.x - 1)) || (player_location.x == (bomb_location.x + 1))))) {
                break;
            }
        }
        timesThroughLoop += 1;
        timeForBomb += 1;
    }

    tinygl_clear();

    if (win) {
        tinygl_text("You Win");
    } else {
        tinygl_text("You Lose");
    }
    while (1) {
        tinygl_update ();
        pacer_wait();

    }
}
