/** @file   flasher.c
    @author Matthew Blake (58979250) and James Hay (78055194)
    @date   16 October 2018
    @brief  Flashes players to idenitify them
*/

#include "system.h"
#include "tinygl.h"

#define FLASHER_OFF 0
#define FLASHER_ON 1
#define FLASHER_THRESHOLD_ONE 1000
#define FLASHER_THRESHOLD_TWO 2000

/** Turns a players pixel off */
void flasher_off(tinygl_point_t* player_location, tinygl_point_t* enemy_location)
{
    tinygl_pixel_set(*player_location, FLASHER_OFF);
    tinygl_pixel_set(*enemy_location, FLASHER_OFF);
}

/** Turns a players pixel on */
void flasher_on(tinygl_point_t* player_location, tinygl_point_t* enemy_location)
{
    tinygl_pixel_set(*player_location, FLASHER_ON);
    tinygl_pixel_set(*enemy_location, FLASHER_ON);
}

/** Controls when players should be flashed */
void flasher_pick_flash(tinygl_point_t* player_location, tinygl_point_t* enemy_location, int* timesThroughLoop)
{
    if(*timesThroughLoop == FLASHER_THRESHOLD_ONE) {
        flasher_off(player_location, enemy_location);
    } else if(*timesThroughLoop == FLASHER_THRESHOLD_TWO) {
        flasher_on(player_location, enemy_location);
        *timesThroughLoop = FLASHER_OFF;
    }
    *timesThroughLoop += 1;
}
