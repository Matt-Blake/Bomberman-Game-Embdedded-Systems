// By Matt Blake: 58979250
// &  James Hay: 78055194
// Group 135


#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "tinygl.h"

#define PIEZO1_PIO PIO_DEFINE (PORT_D, 4)
#define PIEZO2_PIO PIO_DEFINE (PORT_D, 6)
#define TONE_FREQUENCY 440

void beep (int freq)
{
    int loopRate = (freq);

    pacer_init (loopRate);

    int tick = 0;

    pio_config_set (PIEZO1_PIO, PIO_OUTPUT_LOW);
    pio_config_set (PIEZO2_PIO, PIO_OUTPUT_HIGH);

    while (tick < 0) {

        pio_output_toggle (PIEZO1_PIO);
        pio_output_toggle (PIEZO2_PIO);

        tick++;
        pacer_wait();
    }
    pio_output_set (PIEZO2_PIO, PIO_OUTPUT_LOW);
    pio_output_set (PIEZO1_PIO, PIO_OUTPUT_LOW);
}

