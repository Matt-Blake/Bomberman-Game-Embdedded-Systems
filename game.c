#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h" // clear stuff out of makefile thats not needed after modulisation etc
#include "pacer.h"
#include "ir_uart.h"
#include "reciever.h"
#include "mapGenerator.h"
#include "sideSelect.h"
#include "flasher.h"
#include "playerMove.h"
#include "bombs.h"
#include "finalText.h"
#include "initalise.h"

//change make file including headers for makefile.
// remeber to change globals to capital and do good variable names
// can maybe mix modules together
// Make stuff private

int main (void)
{
    initalise_program();
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

    sideSelect_select(&player_location, &enemy_location);
    tinygl_clear();
    map_generator_generate();
    tinygl_pixel_set(player_location, 1); // initalise players
    tinygl_pixel_set(enemy_location, 1);

    while (1) {
        tinygl_update();
        navswitch_update();

        reciever_recieve(&enemy_location, &enemy_bomb_location, &win, &enemy_bomb_dropped, &timeForEnemyBomb); // Recieves IR messages
        flasher_pick_flash(&player_location, &enemy_location, &timesThroughLoop); // Flashers the player and enemy to idenitify them
        playerMove_where(&player_location); //  Checks if the player needs to move anywhere
        bombs_tracker(&bomb_location, &enemy_bomb_location, &player_location, &enemy_location, &timeForPlayerBomb, &player_bomb_dropped, &timeForEnemyBomb, &enemy_bomb_dropped, &win); // Handles bomb placement and detonation

        if (win != 0) { // End game statement
            break;
        }
    }

    finalText_select(win);
    finalText_run();
}
