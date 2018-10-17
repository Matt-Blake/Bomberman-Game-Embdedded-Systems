// By Matt Blake: 58979250
// &  James Hay: 78055194
// Group 135


#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"
#include "pacer.h"
#include "ir_uart.h"

#define PACER_RATE 500
#define TEXT_RATE 27

void initalise_program(void)
{
    system_init (); // initalising section, should be modulised probably
    pacer_init (PACER_RATE);
    tinygl_init (PACER_RATE); // #define this
    ir_uart_init ();
    tinygl_text_speed_set (TEXT_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_font_set (&font5x7_1);
    tinygl_text("PRESS JOYSTICK");
}
