/** @file   mapGenerator.h
    @author Matthew Blake (58979250) and James Hay (78055194)
    @date   16 October 2018
    @brief  Generators the enviroment so bomberman can be played
*/

#include "system.h"
#include "tinygl.h"
#include "navswitch.h"

#define MAPGENERATOR_WALL 1
#define MAPGENERATOR_PATH 0
#define MAPGENERATOR_ROWS 5
#define MAPGENERATOR_COLUMNS 7

/** function used to generate maps */
void map_generator_generate(void);