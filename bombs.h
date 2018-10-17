/** @file   bombs.h
    @author Matthew Blake (58979250) and James Hay (78055194)
    @date   16 October 2018
    @brief  Controls the dropping of bombs
*/

#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "ir_uart.h"

#define BOMBS_OFF 0
#define BOMBS_ON 1
#define BOMBS_LOSE 2
#define BOMBS_FLASH_FIRST 100
#define BOMBS_FLASH_SECOND 200
#define BOMBS_DETONATE 3000

/** Drops a bomb at player_location */
void bombs_drop_bomb(tinygl_point_t* bomb_location, tinygl_point_t* player_location, int* player_bomb_dropped, int* timeForPlayerBomb);

/** Flahes the bomb at a set rate, so the player know its a bomb */
void bombs_flash_bomb(tinygl_point_t* bomb_location, int* bomb_dropped, int* timeforBomb);

/** Destroys the bomb and the surrounding area */
void bombs_detonate(tinygl_point_t* bomb_location, tinygl_point_t* player_location, tinygl_point_t* enemy_location, int* timeForPlayerBomb, int* player_bomb_dropped, int* win);

/** Checks if the game should end, if a player is destroyed */
void bombs_destruction(tinygl_point_t* bomb_location);

/** Detonates the bomb */
void bombs_game_end(tinygl_point_t* bomb_location, tinygl_point_t* player_location, tinygl_point_t* enemy_location, int* win);

/** Controls the operation of bombs */
void bombs_tracker(tinygl_point_t* bomb_location, tinygl_point_t* enemy_bomb_location, tinygl_point_t* player_location, tinygl_point_t* enemy_location, int* timeForPlayerBomb, int* player_bomb_dropped, int* timeForEnemyBomb, int* enemy_bomb_dropped, int* win);