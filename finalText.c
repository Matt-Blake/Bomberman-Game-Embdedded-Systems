/** @file   finalText.c
    @author Matthew Blake (58979250) and James Hay (78055194)
    @date   16 October 2018
    @brief  Controls the text displayed at the end game screen
*/

#include "system.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font5x7_1.h"

#define WIN 1
#define LOSS 2

/** Selects the text to be displayed during the end of the game*/
void finalText_select(int win)
{
    tinygl_clear();
    if (win == WIN) {
        tinygl_text("YOU WIN");
    } else if (win == LOSS) {
        tinygl_text("YOU LOSE");
    }
}

/** Displays the final text */
void finalText_run(void)
{
    while (1) {
        tinygl_update();
        pacer_wait();
    }
}
