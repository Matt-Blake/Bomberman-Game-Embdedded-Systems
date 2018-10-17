// By Matt Blake: 58979250
// &  James Hay: 78055194
// Group 135


#include "system.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "navswitch.h"

void sideSelect_select(tinygl_point_t* player_location, tinygl_point_t* enemy_location)
{
    char d = 0;
    tinygl_point_t player_2 = {4, 6}; // fix variable names
    while (1) { // side selection section

        tinygl_update();
        navswitch_update();
        pacer_wait();

        if (ir_uart_read_ready_p ()) { // if other player seclect first
            d = ir_uart_getc ();
            if (d == 'A') {
                player_location->x = player_2.x;
                player_location->y = player_2.y;
                break;
            }
        } else if (navswitch_push_event_p (NAVSWITCH_PUSH)) { // if you select first
            ir_uart_putc ('A'); // is this the right thing?
            enemy_location->x = player_2.x;
            enemy_location->y = player_2.y;
            break;
        }
    }
}
