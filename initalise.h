/** @file   initalise.h
    @author Matthew Blake (58979250) and James Hay (78055194)
    @date   16 October 2018
    @brief  Initalises the Bomberman game
*/

#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"
#include "pacer.h"
#include "ir_uart.h"

#define PACER_RATE 500
#define TEXT_RATE 27

/** Initalises the game */
void initalise_program(void);