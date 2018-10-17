/** @file   reciever.c
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
void reciever_move_north(tinygl_point_t* enemy_location)
{
    tinygl_pixel_set(*enemy_location, 0);
    enemy_location->y -= 1;
    tinygl_pixel_set(*enemy_location, 1);
}

/** Moves the enemy player South on the LED Display */
void reciever_move_south(tinygl_point_t* enemy_location)
{
    tinygl_pixel_set(*enemy_location, 0);
    enemy_location->y += 1;
    tinygl_pixel_set(*enemy_location, 1);
}

/** Moves the enemy player East on the LED Display */
void reciever_move_east(tinygl_point_t* enemy_location)
{
    tinygl_pixel_set(*enemy_location, 0);
    enemy_location->x += 1;
    tinygl_pixel_set(*enemy_location, 1);
}

/** Moves the enemy player West on the LED Display */
void reciever_move_west(tinygl_point_t* enemy_location)
{
    tinygl_pixel_set(*enemy_location, 0);
    enemy_location->x -= 1;
    tinygl_pixel_set(*enemy_location, 1);
}

/** Drops an enemy bomb */
void reciever_bomb_drop(tinygl_point_t* enemy_location, tinygl_point_t* enemy_bomb_location, int* enemy_bomb_dropped)
{
    enemy_bomb_location->x = enemy_location->x; // modulise this further?
    enemy_bomb_location->y = enemy_location->y;
    *enemy_bomb_dropped = 1;
}

/** Detonates an enemy bomb */
void reciever_bomb_explosion(tinygl_point_t* enemy_bomb_location, int* timeForEnemyBomb, int* enemy_bomb_dropped)
{
    tinygl_pixel_set(tinygl_point (enemy_bomb_location->x + 1, enemy_bomb_location->y), 0);    // neaten all this up
    tinygl_pixel_set(tinygl_point (enemy_bomb_location->x - 1, enemy_bomb_location->y), 0);
    tinygl_pixel_set(tinygl_point (enemy_bomb_location->x, enemy_bomb_location->y + 1), 0);
    tinygl_pixel_set(tinygl_point (enemy_bomb_location->x, enemy_bomb_location->y - 1), 0);
    tinygl_pixel_set(*enemy_bomb_location, 0);
    *timeForEnemyBomb = 0;
    *enemy_bomb_dropped = 0;
}

/** Controls the recieving and interpreting of messages */
void reciever_recieve(tinygl_point_t* enemy_location, tinygl_point_t* enemy_bomb_location, int* win, int* enemy_bomb_dropped, int* timeForEnemyBomb)
{
    if (ir_uart_read_ready_p ()) {
        char message = 0;
        message = ir_uart_getc ();
        if (message == 'N') {
            reciever_move_north(enemy_location);
        } else if(message == 'S') {
            reciever_move_south(enemy_location);
        } else if(message == 'E') {
            reciever_move_east(enemy_location);
        } else if(message == 'F') {
            reciever_move_west(enemy_location);
        } else if(message == 'W') {
            *win = RECIEVER_WIN;
        } else if(message == 'L') {
            *win = RECIEVER_LOSS;
        } else if(message == 'B') {
            reciever_bomb_drop(enemy_location, enemy_bomb_location, enemy_bomb_dropped);
        } else if(message == 'P') {
            reciever_bomb_explosion(enemy_bomb_location, timeForEnemyBomb, enemy_bomb_dropped);
        }
    }
}
