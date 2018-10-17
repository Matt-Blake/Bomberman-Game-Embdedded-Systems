/** @file   game.c
    @author Matthew Blake (58979250) and James Hay (78055194)
    @date   16 October 2018
    @brief  Runs the bomberman game
*/

#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"
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

#define GAME_UNFINISHED 0
#define PIXEL_ON 1

/** main function that runs the Bomberman game */
int main (void)
{
    initalise_program();
    tinygl_point_t bomb_location = {0, 0};
    tinygl_point_t enemy_bomb_location = {0, 0};
    tinygl_point_t player_location = {0, 0};
    tinygl_point_t enemy_location = {0, 0};

    int times_through_loop = 0;
    int time_for_player_Bomb = 0;
    int time_for_enemy_bomb = 0;
    int player_bomb_dropped = 0;
    int enemy_bomb_dropped = 0;
    int win = 0;

    sideSelect_select(&player_location, &enemy_location);
    tinygl_clear();
    map_generator_generate();
    tinygl_pixel_set(player_location, PIXEL_ON); // Initalise players
    tinygl_pixel_set(enemy_location, PIXEL_ON);

    while (1) {
        tinygl_update();
        navswitch_update();
        reciever_recieve(&enemy_location, &enemy_bomb_location, &win, &enemy_bomb_dropped, &time_for_enemy_bomb); // Recieves IR messages
        flasher_pick_flash(&player_location, &enemy_location, &times_through_loop); // Flashers the player and enemy to idenitify them
        playerMove_where(&player_location); //  Checks if the player needs to move anywhere
        bombs_tracker(&bomb_location, &enemy_bomb_location, &player_location, &enemy_location, &time_for_player_Bomb, &player_bomb_dropped, &time_for_enemy_bomb, &enemy_bomb_dropped, &win); // Handles bomb placement and detonation

        if (win != GAME_UNFINISHED) { // End game statement
            break;
        }
    }

    finalText_select(win);
    finalText_run(); // Displays win/loss text once game is finished
    return 0;
}
