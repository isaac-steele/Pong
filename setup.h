/** @file paddle.c
    @author K. Lindsay
    @date 9 August 2023
    @brief Header file for game setup
*/


#include "system.h"
#include "tinygl.h"

typedef struct {
    bool player1;
    bool has_ball;
} Player_info_t;


void selectPlayer(Player_info_t player);