#include "system.h"
#include "tinygl.h"

void flasher_off(tinygl_point_t* player_location, tinygl_point_t* enemy_location);

void flasher_on(tinygl_point_t* player_location, tinygl_point_t* enemy_location);

void flasher_pick_flash(tinygl_point_t* player_location, tinygl_point_t* enemy_location, int* timesThroughLoop);
