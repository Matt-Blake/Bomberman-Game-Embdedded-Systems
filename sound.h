#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "tinygl.h"

#define PIEZO2_PIO PIO_DEFINE (PORT_D, 6)

void beep (int freq);
