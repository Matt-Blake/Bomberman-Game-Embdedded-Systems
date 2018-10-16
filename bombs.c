#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "ir_uart.h"

void bombs_drop_bomb(tinygl_point_t* bomb_location, tinygl_point_t* player_location, int* player_bomb_dropped, int* timeForPlayerBomb)
{
    *player_bomb_dropped = 1;
    *timeForPlayerBomb = 0;
    bomb_location->x = player_location->x;
    bomb_location->y = player_location->y;
    tinygl_pixel_set(*bomb_location, 1);
    ir_uart_putc ('B');
}

void bombs_flash_bomb(tinygl_point_t* bomb_location, int* bomb_dropped, int* timeForBomb)
{
    if(((*timeForBomb % 200) == 0 && (*bomb_dropped == 1))) { // flahes bomb
        tinygl_pixel_set(*bomb_location, 0);
    } else if(((*timeForBomb % 100) == 0) && (*bomb_dropped == 1)) {
        tinygl_pixel_set(*bomb_location, 1);
    }
}

void bombs_destruction(tinygl_point_t* bomb_location)
{
    tinygl_pixel_set(tinygl_point (bomb_location->x + 1, bomb_location->y), 0); // neaten all this up
    tinygl_pixel_set(tinygl_point (bomb_location->x - 1, bomb_location->y), 0);
    tinygl_pixel_set(tinygl_point (bomb_location->x, bomb_location->y + 1), 0);
    tinygl_pixel_set(tinygl_point (bomb_location->x, bomb_location->y - 1), 0);
    tinygl_pixel_set(*bomb_location, 0);
}

void bombs_game_end(tinygl_point_t* bomb_location, tinygl_point_t* player_location, tinygl_point_t* enemy_location, int* win)
{
    if (((player_location->x == bomb_location->x) && ((player_location->y == bomb_location->y) || (player_location->y == (bomb_location->y - 1)) || (player_location->y == (bomb_location->y + 1)))) || ((player_location->y == bomb_location->y) && ((player_location->x == bomb_location->x) || (player_location->x == (bomb_location->x - 1)) || (player_location->x == (bomb_location->x + 1))))) {
        if (((enemy_location->x == bomb_location->x) && ((enemy_location->y == bomb_location->y) || (enemy_location->y == (bomb_location->y - 1)) || (enemy_location->y == (bomb_location->y + 1)))) || ((enemy_location->y == bomb_location->y) && ((enemy_location->x == bomb_location->x) || (enemy_location->x == (bomb_location->x - 1)) || (enemy_location->x == (bomb_location->x + 1))))) {
            ir_uart_putc ('L');
        }
        ir_uart_putc ('W');
        *win = 2;
        //break; // Do these need to be here

    } else if (((enemy_location->x == bomb_location->x) && ((enemy_location->y == bomb_location->y) || (enemy_location->y == (bomb_location->y - 1)) || (enemy_location->y == (bomb_location->y + 1)))) || ((enemy_location->y == bomb_location->y) && ((enemy_location->x == bomb_location->x) || (enemy_location->x == (bomb_location->x - 1)) || (enemy_location->x == (bomb_location->x + 1))))) {
        ir_uart_putc ('L');
        *win = 1;
        //break;
    }
}
void bombs_detonate(tinygl_point_t* bomb_location, tinygl_point_t* player_location, tinygl_point_t* enemy_location, int* timeForPlayerBomb, int* player_bomb_dropped, int* win)
{
    if ((*timeForPlayerBomb == 3000) && (*player_bomb_dropped == 1)) { // bomb explosion
        ir_uart_putc ('P');
        bombs_destruction(bomb_location);
        *timeForPlayerBomb = 0;
        *player_bomb_dropped = 0;
        bombs_game_end(bomb_location, player_location, enemy_location, win);
    }
}

void bombs_tracker(tinygl_point_t* bomb_location, tinygl_point_t* enemy_bomb_location, tinygl_point_t* player_location, tinygl_point_t* enemy_location, int* timeForPlayerBomb, int* player_bomb_dropped, int* timeForEnemyBomb, int* enemy_bomb_dropped, int* win)
{
    if (navswitch_push_event_p (NAVSWITCH_PUSH) && (*player_bomb_dropped == 0)) {
        bombs_drop_bomb(bomb_location, player_location, player_bomb_dropped, timeForPlayerBomb);
    }
    bombs_flash_bomb(bomb_location, player_bomb_dropped, timeForPlayerBomb);
    bombs_flash_bomb(enemy_bomb_location, enemy_bomb_dropped, timeForEnemyBomb);
    bombs_detonate(bomb_location, player_location, enemy_location, timeForPlayerBomb, player_bomb_dropped, win);

    *timeForPlayerBomb += 1;
    *timeForEnemyBomb += 1;
}
