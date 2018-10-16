#include "system.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font5x7_1.h"

void finalText_select(int win)
{
    tinygl_clear();
    if (win == 1) {
        tinygl_text("YOU WIN");
    } else if (win == 2) {
        tinygl_text("YOU LOSE");
    }
}

void finalText_run(void)
{
    while (1) {
        tinygl_update ();
        pacer_wait();
    }
}
