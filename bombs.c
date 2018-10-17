/** @file   bombs.c
    @author Matthew Blake (58979250) and James Hay (78055194)
    @date   16 October 2018
    @brief  Controls the dropping of bombs
*/

#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "ir_uart.h"

#define BOMBS_OFF 0
#define BOMBS_ON 1
#define BOMBS_LOSE 2
#define BOMBS_FLASH_FIRST 100
#define BOMBS_FLASH_SECOND 200
#define BOMBS_DETONATE 3000

/** Drops a bomb at player_location */
void bombs_drop_bomb(tinygl_point_t* bomb_location, tinygl_point_t* player_location, int* player_bomb_dropped, int* timeForPlayerBomb)
{
    *player_bomb_dropped = BOMBS_ON;
    *timeForPlayerBomb = BOMBS_OFF;
    bomb_location->x = player_location->x;
    bomb_location->y = player_location->y;
    tinygl_pixel_set(*bomb_location, BOMBS_ON);
    ir_uart_putc ('B');
}

/** Flahes the bomb at a set rate, so the player know its a bomb */
void bombs_flash_bomb(tinygl_point_t* bomb_location, int* bomb_dropped, int* timeForBomb)
{
    if(((*timeForBomb % BOMBS_FLASH_SECOND) == BOMBS_OFF && (*bomb_dropped == BOMBS_ON))) {
        tinygl_pixel_set(*bomb_location, BOMBS_OFF);
    } else if(((*timeForBomb % BOMBS_FLASH_FIRST) == BOMBS_OFF) && (*bomb_dropped == BOMBS_ON)) {
        tinygl_pixel_set(*bomb_location, BOMBS_ON);
    }
}

/** Destroys the bomb and the surrounding area */
void bombs_destruction(tinygl_point_t* bomb_location)
{
    tinygl_pixel_set(tinygl_point (bomb_location->x + 1, bomb_location->y), BOMBS_OFF);
    tinygl_pixel_set(tinygl_point (bomb_location->x - 1, bomb_location->y), BOMBS_OFF);
    tinygl_pixel_set(tinygl_point (bomb_location->x, bomb_location->y + 1), BOMBS_OFF);
    tinygl_pixel_set(tinygl_point (bomb_location->x, bomb_location->y - 1), BOMBS_OFF);
    tinygl_pixel_set(*bomb_location, BOMBS_OFF);
}

/** Checks if the game should end, if a player is destroyed */
void bombs_game_end(tinygl_point_t* bomb_location, tinygl_point_t* player_location, tinygl_point_t* enemy_location, int* win)
{
    if (((player_location->x == bomb_location->x) && ((player_location->y == bomb_location->y) || (player_location->y == (bomb_location->y - 1)) || (player_location->y == (bomb_location->y + 1)))) || ((player_location->y == bomb_location->y) && ((player_location->x == bomb_location->x) || (player_location->x == (bomb_location->x - 1)) || (player_location->x == (bomb_location->x + 1))))) {
        if (((enemy_location->x == bomb_location->x) && ((enemy_location->y == bomb_location->y) || (enemy_location->y == (bomb_location->y - 1)) || (enemy_location->y == (bomb_location->y + 1)))) || ((enemy_location->y == bomb_location->y) && ((enemy_location->x == bomb_location->x) || (enemy_location->x == (bomb_location->x - 1)) || (enemy_location->x == (bomb_location->x + 1))))) {
            ir_uart_putc ('L');
        }
        ir_uart_putc ('W');
        *win = BOMBS_LOSE;

    } else if (((enemy_location->x == bomb_location->x) && ((enemy_location->y == bomb_location->y) || (enemy_location->y == (bomb_location->y - 1)) || (enemy_location->y == (bomb_location->y + 1)))) || ((enemy_location->y == bomb_location->y) && ((enemy_location->x == bomb_location->x) || (enemy_location->x == (bomb_location->x - 1)) || (enemy_location->x == (bomb_location->x + 1))))) {
        ir_uart_putc ('L');
        *win = BOMBS_ON;
    }
}

/** Detonates the bomb */
void bombs_detonate(tinygl_point_t* bomb_location, tinygl_point_t* player_location, tinygl_point_t* enemy_location, int* timeForPlayerBomb, int* player_bomb_dropped, int* win)
{
    if ((*timeForPlayerBomb == BOMBS_DETONATE) && (*player_bomb_dropped == BOMBS_ON)) {
        ir_uart_putc ('P');
        bombs_destruction(bomb_location);
        *timeForPlayerBomb = BOMBS_OFF;
        *player_bomb_dropped = BOMBS_OFF;
        bombs_game_end(bomb_location, player_location, enemy_location, win);
    }
}

/** Controls the operation of bombs */
void bombs_tracker(tinygl_point_t* bomb_location, tinygl_point_t* enemy_bomb_location, tinygl_point_t* player_location, tinygl_point_t* enemy_location, int* timeForPlayerBomb, int* player_bomb_dropped, int* timeForEnemyBomb, int* enemy_bomb_dropped, int* win)
{
    if (navswitch_push_event_p (NAVSWITCH_PUSH) && (*player_bomb_dropped == BOMBS_OFF)) {
        bombs_drop_bomb(bomb_location, player_location, player_bomb_dropped, timeForPlayerBomb);
    }
    bombs_flash_bomb(bomb_location, player_bomb_dropped, timeForPlayerBomb);
    bombs_flash_bomb(enemy_bomb_location, enemy_bomb_dropped, timeForEnemyBomb);
    bombs_detonate(bomb_location, player_location, enemy_location, timeForPlayerBomb, player_bomb_dropped, win);

    *timeForPlayerBomb += 1;
    *timeForEnemyBomb += 1;
}
