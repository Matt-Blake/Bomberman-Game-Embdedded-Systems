/** @file   playerMove.h
    @author Matthew Blake (58979250) and James Hay (78055194)
    @date   16 October 2018
    @brief  Moves the player around the map
*/

#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "ir_uart.h"

#define PLAYERMOVE_MAX_ROW 4
#define PLAYERMOVE_MAX_COL 6
#define PLAYERMOVE_MIN_LOCATION 0

/** Moves the player North */
void playerMove_north(tinygl_point_t* player_location);

/** Moves the player South */
void playerMove_south(tinygl_point_t* player_location);

/** Moves the player East */
void playerMove_east(tinygl_point_t* player_location);

/** Moves the player West */
void playerMove_west(tinygl_point_t* player_location);

/** Determines where the player should move */
void playerMove_where(tinygl_point_t* player_location);