#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "ir_uart.h"

void bombs_drop_bomb(tinygl_point_t* bomb_location, tinygl_point_t* player_location, int* player_bomb_dropped, int* timeForPlayerBomb);

void bombs_flash_bomb(tinygl_point_t* bomb_location, int* bomb_dropped, int* timeforBomb);

void bombs_detonate(tinygl_point_t* bomb_location, tinygl_point_t* player_location, tinygl_point_t* enemy_location, int* timeForPlayerBomb, int* player_bomb_dropped, int* win);

void bombs_destruction(tinygl_point_t* bomb_location);

void bombs_game_end(tinygl_point_t* bomb_location, tinygl_point_t* player_location, tinygl_point_t* enemy_location, int* win);

void bombs_tracker(tinygl_point_t* bomb_location, tinygl_point_t* enemy_bomb_location, tinygl_point_t* player_location, tinygl_point_t* enemy_location, int* timeForPlayerBomb, int* player_bomb_dropped, int* timeForEnemyBomb, int* enemy_bomb_dropped, int* win);
