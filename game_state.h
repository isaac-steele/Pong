/** @file paddle.c
    @author K. Lindsay
    @date 9 August 2023
    @brief Display text for different game states including score
*/


#include "system.h"
#include "tinygl.h"

/* game state, contains all key information about current game state*/
typedef struct {
    uint8_t score;
    uint8_t opponent_score;
    uint8_t mode; //game modes: SETUP==0, PLAY == 1, DISPLAY_SCORE == 2
    bool has_ball;
} Game_state_t;


void game_over(Game_state_t* game);
void display_game_start(void);
void display_scores(Game_state_t* game, char scores[7]);