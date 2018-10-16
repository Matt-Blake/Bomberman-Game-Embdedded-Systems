#include "system.h"
#include "tinygl.h"
#include "ir_uart.h"

void reciever_move_north(tinygl_point_t* enemy_location)
{
    tinygl_pixel_set(*enemy_location, 0);
    enemy_location->y -= 1;
    tinygl_pixel_set(*enemy_location, 1);
}

void reciever_move_south(tinygl_point_t* enemy_location)
{
    tinygl_pixel_set(*enemy_location, 0);
    enemy_location->y += 1;
    tinygl_pixel_set(*enemy_location, 1);
}

void reciever_move_east(tinygl_point_t* enemy_location)
{
    tinygl_pixel_set(*enemy_location, 0);
    enemy_location->x += 1;
    tinygl_pixel_set(*enemy_location, 1);
}

void reciever_move_west(tinygl_point_t* enemy_location)
{
    tinygl_pixel_set(*enemy_location, 0);
    enemy_location->x -= 1;
    tinygl_pixel_set(*enemy_location, 1);
}

void reciever_bomb_drop(tinygl_point_t* enemy_location, tinygl_point_t* enemy_bomb_location, int* enemy_bomb_dropped)
{
    enemy_bomb_location->x = enemy_location->x; // modulise this further?
    enemy_bomb_location->y = enemy_location->y;
    *enemy_bomb_dropped = 1;
}

void reciever_bomb_explosion(tinygl_point_t* enemy_bomb_location, int* timeForEnemyBomb, int* enemy_bomb_dropped)
{
    tinygl_pixel_set(tinygl_point (enemy_bomb_location->x + 1, enemy_bomb_location->y), 0);    // neaten all this up
    tinygl_pixel_set(tinygl_point (enemy_bomb_location->x - 1, enemy_bomb_location->y), 0);
    tinygl_pixel_set(tinygl_point (enemy_bomb_location->x, enemy_bomb_location->y + 1), 0);
    tinygl_pixel_set(tinygl_point (enemy_bomb_location->x, enemy_bomb_location->y - 1), 0);
    tinygl_pixel_set(*enemy_bomb_location, 0);
    *timeForEnemyBomb = 0;
    *enemy_bomb_dropped = 0;
}

void reciever_recieve(tinygl_point_t* enemy_location, tinygl_point_t* enemy_bomb_location, int* win, int* enemy_bomb_dropped, int* timeForEnemyBomb)
{
    char c = 0;
    c = ir_uart_getc ();
    if (c == 'N') {
        reciever_move_north(enemy_location);
    } else if (c == 'S') {
        reciever_move_south(enemy_location);
    } else if (c == 'E') {
        reciever_move_east(enemy_location);
    } else if (c == 'F') {
        reciever_move_west(enemy_location);
    } else if (c == 'W') {
        *win = 1;
    } else if (c == 'L') {
        *win = 2;
    } else if (c == 'B') {
        reciever_bomb_drop(enemy_location, enemy_bomb_location, enemy_bomb_dropped);
    } else if (c == 'P') {
        reciever_bomb_explosion(enemy_bomb_location, timeForEnemyBomb, enemy_bomb_dropped);
    }
}
