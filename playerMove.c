#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "ir_uart.h"

void playerMove_north(tinygl_point_t* player_location)
{
    if ((tinygl_pixel_get (tinygl_point (player_location->x, (player_location->y - 1)))) == 0) {
        tinygl_pixel_set(*player_location, 0);
        player_location->y -= 1;
        tinygl_pixel_set(*player_location, 1);
        ir_uart_putc ('N');
    }
}

void playerMove_south(tinygl_point_t* player_location)
{
    if ((tinygl_pixel_get (tinygl_point (player_location->x, (player_location->y + 1)))) == 0) {
        tinygl_pixel_set(*player_location, 0);
        player_location->y += 1;
        tinygl_pixel_set(*player_location, 1);
        ir_uart_putc ('S');
    }
}

void playerMove_east(tinygl_point_t* player_location)
{
    if ((tinygl_pixel_get (tinygl_point ((player_location->x + 1), player_location->y))) == 0) {
        tinygl_pixel_set(*player_location, 0);
        player_location->x += 1;
        tinygl_pixel_set(*player_location, 1);
        ir_uart_putc ('E');
    }
}

void playerMove_west(tinygl_point_t* player_location)
{
    if ((tinygl_pixel_get (tinygl_point ((player_location->x - 1), player_location->y))) == 0) {
        tinygl_pixel_set(*player_location, 0);
        player_location->x -= 1;
        tinygl_pixel_set(*player_location, 1);
        ir_uart_putc ('F');
    }
}

void playerMove_where(tinygl_point_t* player_location)
{
    if (navswitch_push_event_p (NAVSWITCH_NORTH) && (player_location->y > 0)) {
        playerMove_north(player_location);
    }

    if (navswitch_push_event_p (NAVSWITCH_SOUTH) && (player_location->y < 6)) {
        playerMove_south(player_location);
    }

    if (navswitch_push_event_p (NAVSWITCH_EAST) && (player_location->x < 4)) {
        playerMove_east(player_location);
    }

    if (navswitch_push_event_p (NAVSWITCH_WEST) && (player_location->x > 0)) {
        playerMove_west(player_location);
    }
}
