/** @file   sideSelect.h
    @author Matthew Blake (58979250) and James Hay (78055194)
    @date   16 October 2018
    @brief  Chooses a side for each player
*/

#include "system.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "navswitch.h"
#include "pacer.h"

#define SIDESELECT_ROWS 4
#define SIDESELECT_COLUMNS 6

/** Selects a side based on who presses down the joystick first */
void sideSelect_select(tinygl_point_t* player_location, tinygl_point_t* enemy_location);