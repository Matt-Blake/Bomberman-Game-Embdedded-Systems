/** @file   reciever.h
    @author Matthew Blake (58979250) and James Hay (78055194)
    @date   16 October 2018
    @brief  Recieves and executes IR instructions
*/

#include "system.h"
#include "tinygl.h"
#include "ir_uart.h"

#define RECIEVER_WIN 1
#define RECIEVER_LOSS 2

/** Moves the enemy player North on the LED Display */
void reciever_move_north(tinygl_point_t* enemy_location);

/** Moves the enemy player South on the LED Display */
void reciever_move_south(tinygl_point_t* enemy_location);

/** Moves the enemy player East on the LED Display */
void reciever_move_east(tinygl_point_t* enemy_location);

/** Moves the enemy player West on the LED Display */
void reciever_move_west(tinygl_point_t* enemy_location);

/** Drops an enemy bomb */
void reciever_bomb_drop(tinygl_point_t* enemy_location, int* enemy_bomb_dropped);

/** Detonates an enemy bomb */
void reciever_bomb_explosion(tinygl_point_t* enemy_location, int* enemy_bomb_dropped);

/** Controls the recieving and interpreting of messages */
void reciever_recieve(tinygl_point_t* enemy_location, tinygl_point_t* enemy_bomb_location, int* win, int* enemy_bomb_dropped, int* timeForEnemyBomb);