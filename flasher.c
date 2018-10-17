// By Matt Blake: 58979250
// &  James Hay: 78055194
// Group 135


#include "system.h"
#include "tinygl.h"

void flasher_off(tinygl_point_t* player_location, tinygl_point_t* enemy_location)
{
    tinygl_pixel_set(*player_location, 0);
    tinygl_pixel_set(*enemy_location, 0);
}

void flasher_on(tinygl_point_t* player_location, tinygl_point_t* enemy_location)
{
    tinygl_pixel_set(*player_location, 1);
    tinygl_pixel_set(*enemy_location, 1);
}

void flasher_pick_flash(tinygl_point_t* player_location, tinygl_point_t* enemy_location, int* timesThroughLoop)
{
    if(*timesThroughLoop == 1000) {
        flasher_off(player_location, enemy_location);
    } else if(*timesThroughLoop == 2000) {
        flasher_on(player_location, enemy_location);
        *timesThroughLoop = 0;
    }
    *timesThroughLoop += 1;
}
