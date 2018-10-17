/** @file   sideSelect.c
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
void sideSelect_select(tinygl_point_t* player_location, tinygl_point_t* enemy_location)
{
    char message = 0;
    tinygl_point_t player_2 = {SIDESELECT_ROWS, SIDESELECT_COLUMNS}; // fix variable names
    while (1) { // side selection section
        tinygl_update();
        navswitch_update();
        pacer_wait();
        if (ir_uart_read_ready_p ()) { // if other player seclect first
            message = ir_uart_getc ();
            if (message == 'A') {
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
