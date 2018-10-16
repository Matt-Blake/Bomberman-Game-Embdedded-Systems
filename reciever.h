/** @file   display.h
    @author M. P. Hayes, UCECE
    @date   23 August 2010
    @brief  Bit-mapped display driver.

    @defgroup display Bit-mapped display driver

    This module implements a simple display frame-buffer.  It abstracts the
    multiplexing of a LED matrix display.
*/
#include "system.h"
#include "tinygl.h"
#include "ir_uart.h"

#include "system.h"
#include "tinygl.h"
#include "ir_uart.h"

void reciever_move_north(tinygl_point_t* enemy_location);

void reciever_move_south(tinygl_point_t* enemy_location);

void reciever_move_east(tinygl_point_t* enemy_location);

void reciever_move_west(tinygl_point_t* enemy_location);

void reciever_bomb_drop(tinygl_point_t* enemy_location, int* enemy_bomb_dropped);

void reciever_bomb_explosion(tinygl_point_t* enemy_location, int* enemy_bomb_dropped);

void reciever_recieve(tinygl_point_t* enemy_location, tinygl_point_t* enemy_bomb_location, int* win, int* enemy_bomb_dropped, int* timeForEnemyBomb);
