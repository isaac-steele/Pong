/** @file paddle.c
    @author K. Lindsay
    @date 9 August 2023
    @brief Display text for different game states including score
*/

#include "game_state.h"
#include "tinygl.h"
#define GAME_OVER 10


void game_over(Game_state_t* game)
{
    game->mode = GAME_OVER;
    tinygl_clear();
    if(game->opponent_score == 5){
        tinygl_text ("DEFEAT! PRESS TO PLAY AGAIN\0");
    } else {
        tinygl_text ("VICTORY! PRESS TO PLAY AGAIN\0");
    }
}

void display_game_start(void)
{
    tinygl_clear();
    tinygl_text ("WELCOME TO PONG! PRESS TO START\0");
}

void display_scores(Game_state_t* game, char scores[7])
{   
    char buffer[2];
    buffer[0] = scores[game->opponent_score];
    buffer[1] = '\0';
    tinygl_text (buffer);
}
