/** @file paddle.c
    @author Kade Lindsay kli107, Isaac Steele ist46
    @date 9 August 2023
    @brief Display text for different game states including score
*/


#include "system.h"
#include "tinygl.h"

#ifndef GAME_STATE_H
#define GAME_STATE_H

/** Contains all key information about current state of play
 * Mode information is encoded as int's to allow for easy transmit
*/
typedef struct {
    uint8_t score;
    uint8_t opponent_score;
    uint8_t mode; //game modes: SETUP==0, PLAY == 1, DISPLAY_SCORE == 2, GAME_OVER == 10
    bool has_ball;
} Game_state_t;

/*displays game over screen*/
void game_over(Game_state_t* game);
/*displays the welcome to pong screen*/
void display_game_start(void);
/*displays your opponents current score*/
void display_scores(Game_state_t* game, char scores[7]);

#endif /* GAME_STATE_H*/