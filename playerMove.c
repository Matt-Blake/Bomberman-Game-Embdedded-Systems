/** @file   playerMove.c
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
void playerMove_north(tinygl_point_t* player_location)
{
    if ((tinygl_pixel_get(tinygl_point (player_location->x, (player_location->y - 1)))) == 0) {
        tinygl_pixel_set(*player_location, 0);
        player_location->y -= 1;
        tinygl_pixel_set(*player_location, 1);
        ir_uart_putc ('N');
    }
}

/** Moves the player South */
void playerMove_south(tinygl_point_t* player_location)
{
    if ((tinygl_pixel_get(tinygl_point (player_location->x, (player_location->y + 1)))) == 0) {
        tinygl_pixel_set(*player_location, 0);
        player_location->y += 1;
        tinygl_pixel_set(*player_location, 1);
        ir_uart_putc ('S');
    }
}

/** Moves the player East */
void playerMove_east(tinygl_point_t* player_location)
{
    if ((tinygl_pixel_get(tinygl_point ((player_location->x + 1), player_location->y))) == 0) {
        tinygl_pixel_set(*player_location, 0);
        player_location->x += 1;
        tinygl_pixel_set(*player_location, 1);
        ir_uart_putc ('E');
    }
}

/** Moves the player West */
void playerMove_west(tinygl_point_t* player_location)
{
    if ((tinygl_pixel_get(tinygl_point ((player_location->x - 1), player_location->y))) == 0) {
        tinygl_pixel_set(*player_location, 0);
        player_location->x -= 1;
        tinygl_pixel_set(*player_location, 1);
        ir_uart_putc ('F');
    }
}

/** Determines where the player should move */
void playerMove_where(tinygl_point_t* player_location)
{
    if (navswitch_push_event_p(NAVSWITCH_NORTH) && (player_location->y > PLAYERMOVE_MIN_LOCATION)) {
        playerMove_north(player_location);
    }
    if (navswitch_push_event_p(NAVSWITCH_SOUTH) && (player_location->y < PLAYERMOVE_MAX_COL)) {
        playerMove_south(player_location);
    }
    if (navswitch_push_event_p(NAVSWITCH_EAST) && (player_location->x < PLAYERMOVE_MAX_ROW)) {
        playerMove_east(player_location);
    }
    if (navswitch_push_event_p(NAVSWITCH_WEST) && (player_location->x > PLAYERMOVE_MIN_LOCATION)) {
        playerMove_west(player_location);
    }
}
