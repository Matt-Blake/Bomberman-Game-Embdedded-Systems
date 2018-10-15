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

    tinygl_point_t player_2 = {4, 6}; // fix variable names
    tinygl_point_t bomb_location = {0, 0};
    tinygl_point_t enemy_bomb_location = {0, 0};

    tinygl_point_t player_location = {0, 0};
    tinygl_point_t enemy_location = {0, 0}; // change this later.

    int timesThroughLoop = 0;
    int timeForPlayerBomb = 0;
    int timeForEnemyBomb = 0;
    int player_bomb_dropped = 0;
    int enemy_bomb_dropped = 0;
    int win = 0;
    char c = 0;
    char d = 0;

    while (1) { // side selection section
        navswitch_update();

        if (ir_uart_read_ready_p ()) { // if other player seclect first
            d = ir_uart_getc ();
            if (d == 'A') {
                player_location.x = player_2.x;
                player_location.y = player_2.y;
                break;
            }
        } else if (navswitch_push_event_p (NAVSWITCH_PUSH)) { // if you select first
            ir_uart_putc ('A'); // is this the right thing?
            enemy_location.x = player_2.x;
            enemy_location.y = player_2.y;
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
            c = ir_uart_getc ();
            if (c == 'N') {
                tinygl_pixel_set(enemy_location, 0);
                enemy_location.y -= 1;
                tinygl_pixel_set(enemy_location, 1);
            } else if (c == 'S') {
                tinygl_pixel_set(enemy_location, 0);
                enemy_location.y += 1;
                tinygl_pixel_set(enemy_location, 1);
            } else if (c == 'E') {
                tinygl_pixel_set(enemy_location, 0);
                enemy_location.x += 1;
                tinygl_pixel_set(enemy_location, 1);
            } else if (c == 'F') {
                tinygl_pixel_set(enemy_location, 0);
                enemy_location.x -= 1;
                tinygl_pixel_set(enemy_location, 1);

            } else if (c == 'W') { // change back to else if
                win = 1;
                break;
            } else if (c == 'L') {
                break;
            } else if (c == 'B') {
                enemy_bomb_location.x = enemy_location.x;
                enemy_bomb_location.y = enemy_location.y;
                enemy_bomb_dropped = 1;
            } else if (c == 'P') {
                tinygl_pixel_set(tinygl_point (enemy_bomb_location.x + 1, enemy_bomb_location.y), path);    // neaten all this up
                tinygl_pixel_set(tinygl_point (enemy_bomb_location.x - 1, enemy_bomb_location.y), path);
                tinygl_pixel_set(tinygl_point (enemy_bomb_location.x, enemy_bomb_location.y + 1), path);
                tinygl_pixel_set(tinygl_point (enemy_bomb_location.x, enemy_bomb_location.y - 1), path);
                tinygl_pixel_set(enemy_bomb_location, 0);
                timeForEnemyBomb = 0;
                enemy_bomb_dropped = 0;
            }
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
                ir_uart_putc ('N');
            }
        }


        if (navswitch_push_event_p (NAVSWITCH_SOUTH) && (player_location.y < 6)) { // modulise all this stuff and remove constants
            if ((tinygl_pixel_get (tinygl_point (player_location.x, player_location.y + 1))) == 0) {
                tinygl_pixel_set(player_location, 0);
                player_location.y += 1;
                tinygl_pixel_set(player_location, 1);
                ir_uart_putc ('S');
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_EAST) && (player_location.x < 4)) { // modulise all this stuff and remove constants
            if ((tinygl_pixel_get (tinygl_point (player_location.x + 1, player_location.y))) == 0) {
                tinygl_pixel_set(player_location, 0);
                player_location.x += 1;
                tinygl_pixel_set(player_location, 1);
                ir_uart_putc ('E');
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_WEST) && (player_location.x > 0)) { // modulise all this stuff and remove constants
            if ((tinygl_pixel_get (tinygl_point (player_location.x - 1, player_location.y))) == 0) {
                tinygl_pixel_set(player_location, 0);
                player_location.x -= 1;
                tinygl_pixel_set(player_location, 1);
                ir_uart_putc ('F');
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_PUSH) && !player_bomb_dropped) { // drop bomb
            player_bomb_dropped = 1;
            timeForPlayerBomb = 0;
            bomb_location.x = player_location.x;
            bomb_location.y = player_location.y;
            ir_uart_putc ('B');
        }

        if(((timeForPlayerBomb % 200) == 0 && (player_bomb_dropped == 1))) { // flahes bomb
            tinygl_pixel_set(bomb_location, 0);
        } else if(((timeForPlayerBomb % 100) == 0) && (player_bomb_dropped == 1)) {
            tinygl_pixel_set(bomb_location, 1);
        }

        if(((timeForEnemyBomb % 200) == 0 && (enemy_bomb_dropped == 1))) { // flahes enemy bomb
            tinygl_pixel_set(enemy_bomb_location, 0);
        } else if(((timeForEnemyBomb % 100) == 0) && (enemy_bomb_dropped == 1)) {
            tinygl_pixel_set(enemy_bomb_location, 1);
        }

        if ((timeForPlayerBomb == 3000) && (player_bomb_dropped == 1)) { // bomb explosion
            ir_uart_putc ('P');
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
                ir_uart_putc ('W');
                break;

            } else if (((enemy_location.x == bomb_location.x) && ((enemy_location.y == bomb_location.y) || (enemy_location.y == (bomb_location.y - 1)) || (enemy_location.y == (bomb_location.y + 1)))) || ((enemy_location.y == bomb_location.y) && ((enemy_location.x == bomb_location.x) || (enemy_location.x == (bomb_location.x - 1)) || (enemy_location.x == (bomb_location.x + 1))))) {
                ir_uart_putc ('L');
                win = 1;
                break;
            }
        }

        timesThroughLoop += 1;
        timeForPlayerBomb += 1;
        timeForEnemyBomb += 1;
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
