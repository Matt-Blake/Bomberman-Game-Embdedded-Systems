#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h" // clear stuff out of makefile thats not needed after modulisation etc
#include "pacer.h"
#include "ir_uart.h"

#define wall 1 // remeber to change these to capital
#define path 0

int main (void)
{
    system_init (); // initalising section
    pacer_init (500);
    tinygl_init (500); // #define this
    ir_uart_init ();
    tinygl_text_speed_set (20);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_font_set (&font5x7_1);

    /*
        //int location[5][7] = [35][2] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, // Coordinates of map
            {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6},
            {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6},
            {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6},
            {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6},
        };
    */
    int index = 0;

    tinygl_point_t player_2 = {4, 6}; // fix variable names
    tinygl_point_t bomb_location = {0, 0};

    tinygl_point_t player_location = {0, 0};
    tinygl_point_t enemy_location = {0, 0}; // change this later.

    int timesThroughLoop = 0;
    int timeForPlayerBomb = 0;
    //int timeForEnemyBomb = 0;
    int player_bomb_dropped = 0;
    int enemy_bomb_dropped = 0;
    int win = 0;

    while (1) { // side selection section
        navswitch_update();

        if (ir_uart_read_ready_p ()) { // if other player seclect first
            //if (ir_uart_getc () == 'A') {
            player_location.x = player_2.x;
            player_location.y = player_2.y;
            break;
            //}
        } else if (navswitch_push_event_p (NAVSWITCH_PUSH)) { // if you select first
            ir_uart_putc ('A'); // is this the right thing?
            break;
        }
    }

    int map[5][7] = {{path, path, wall, wall, path, path, path}, // map making section
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

    tinygl_pixel_set(player_location, 1); // initalise players
    tinygl_pixel_set(enemy_location, 1);

    while (1) {

        tinygl_update();
        navswitch_update();

        if (ir_uart_read_ready_p ()) { // recieve movement
            //if (ir_uart_getc () == 'M') {
            index = ir_uart_getc () - 48;
            tinygl_pixel_set(enemy_location, 0);
            enemy_location.x = index / 7;
            enemy_location.y = (index / 7) + (index % 7);
            tinygl_pixel_set(enemy_location, 1);
            //}
        }

        if(timesThroughLoop == 1000) { // Flashes the Player and enemy
            tinygl_pixel_set(player_location, 0);
            tinygl_pixel_set(enemy_location, 0);
        } else if(timesThroughLoop == 2000) {
            tinygl_pixel_set(player_location, 1);
            tinygl_pixel_set(enemy_location, 1);
            timesThroughLoop = 0;
        }

        if (navswitch_push_event_p (NAVSWITCH_NORTH) && (player_location.y > 0)) { // movement section, modulise all this stuff
            if ((tinygl_pixel_get (tinygl_point (player_location.x, player_location.y - 1))) == 0) {
                tinygl_pixel_set(player_location, 0);
                player_location.y -= 1;
                tinygl_pixel_set(player_location, 1);
                ir_uart_putc (48 + player_location.y + player_location.x * 7);
            }
        }


        if (navswitch_push_event_p (NAVSWITCH_SOUTH) && (player_location.y < 6)) { // modulise all this stuff and remove constants
            if ((tinygl_pixel_get (tinygl_point (player_location.x, player_location.y + 1))) == 0) {
                tinygl_pixel_set(player_location, 0);
                player_location.y += 1;
                tinygl_pixel_set(player_location, 1);
                ir_uart_putc (48 + player_location.y + player_location.x * 7);
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_EAST) && (player_location.x < 4)) { // modulise all this stuff and remove constants
            if ((tinygl_pixel_get (tinygl_point (player_location.x + 1, player_location.y))) == 0) {
                tinygl_pixel_set(player_location, 0);
                player_location.x += 1;
                tinygl_pixel_set(player_location, 1);
                ir_uart_putc (48 + player_location.y + player_location.x * 7);
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_WEST) && (player_location.x > 0)) { // modulise all this stuff and remove constants
            if ((tinygl_pixel_get (tinygl_point (player_location.x - 1, player_location.y))) == 0) {
                tinygl_pixel_set(player_location, 0);
                player_location.x -= 1;
                tinygl_pixel_set(player_location, 1);
                ir_uart_putc (48 + player_location.y + player_location.x * 7);
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_PUSH) && !player_bomb_dropped) { // drop bomb
            player_bomb_dropped = 1;
            timeForPlayerBomb = 0;
            bomb_location.x = player_location.x;
            bomb_location.y = player_location.y;

        }

        if(((timeForPlayerBomb % 200) == 0 && (player_bomb_dropped == 1))) {
            tinygl_pixel_set(bomb_location, 0);
        } else if(((timeForPlayerBomb % 100) == 0) && (player_bomb_dropped == 1)) {
            tinygl_pixel_set(bomb_location, 1);
        }

        if ((timeForPlayerBomb == 3000) && (player_bomb_dropped == 1)) { // bomb explosion
            tinygl_pixel_set(tinygl_point (bomb_location.x + 1, bomb_location.y), path); // neaten all this up
            tinygl_pixel_set(tinygl_point (bomb_location.x - 1, bomb_location.y), path);
            tinygl_pixel_set(tinygl_point (bomb_location.x, bomb_location.y + 1), path);
            tinygl_pixel_set(tinygl_point (bomb_location.x, bomb_location.y - 1), path);
            tinygl_pixel_set(bomb_location, 0);
            timeForPlayerBomb = 0;
            player_bomb_dropped = 0;
            // win loss conditions
            if (((player_location.x == bomb_location.x) && ((player_location.y == bomb_location.y) || (player_location.y == (bomb_location.y - 1)) || (player_location.y == (bomb_location.y + 1)))) || ((player_location.y == bomb_location.y) && ((player_location.x == bomb_location.x) || (player_location.x == (bomb_location.x - 1)) || (player_location.x == (bomb_location.x + 1))))) {
                if (((enemy_location.x == bomb_location.x) && ((enemy_location.y == bomb_location.y) || (enemy_location.y == (bomb_location.y - 1)) || (enemy_location.y == (bomb_location.y + 1)))) || ((enemy_location.y == bomb_location.y) && ((enemy_location.x == bomb_location.x) || (enemy_location.x == (bomb_location.x - 1)) || (enemy_location.x == (bomb_location.x + 1))))) {
                    ir_uart_putc ('L');
                }
                break;

            } else if (((enemy_location.x == bomb_location.x) && ((enemy_location.y == bomb_location.y) || (enemy_location.y == (bomb_location.y - 1)) || (enemy_location.y == (bomb_location.y + 1)))) || ((enemy_location.y == bomb_location.y) && ((enemy_location.x == bomb_location.x) || (enemy_location.x == (bomb_location.x - 1)) || (enemy_location.x == (bomb_location.x + 1))))) {
                ir_uart_putc ('L');
                win = 1;
                break;
            }
        }
        timesThroughLoop += 1;
        timeForPlayerBomb += 1;
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
