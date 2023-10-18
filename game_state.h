/** @file game_state.h
    @author Kade Lindsay kli107, Isaac Steele ist46
    @date 18 October 2023
    @brief Display text for different game states including score
*/


#include "system.h"
#include "tinygl.h"

#ifndef GAME_STATE_H
#define GAME_STATE_H

#define GAME_OVER 10
#define WINNING_SCORE 5

/** Contains all key information about current state of play
 * Mode information is encoded as int's to allow for easy transmit
*/
typedef struct {
    uint8_t score;
    uint8_t opponent_score;
    uint8_t mode; //game modes: SETUP==0, PLAY == 1, DISPLAY_SCORE == 2, GAME_OVER == 10
    bool has_ball;
} Game_state_t;

/**
 * Displays the game over screen and sets game state to game over
 * @param game pointer to the current state of the game
*/
void game_over(Game_state_t* game);

/*Displays the welcome to pong text*/
void display_game_start(void);

/** Displays the current score of your opponent on your screen
 * @param game pointer to the current game state
 * @param scores List of scores, 0-5 and end of line
*/
void display_scores(Game_state_t* game, char scores[7]);

#endif /* GAME_STATE_H*/