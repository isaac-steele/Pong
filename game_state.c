/** @file game_state.c
    @author Kade Lindsay kli107, Isaac Steele ist46
    @date 18 October 2023
    @brief Display text for different game states including score
*/

#include "game_state.h"
#include "tinygl.h"


/**
 * Displays the game over screen and sets game state to game over
 * @param game Game_state_t pointer
*/
void game_over(Game_state_t* game)
{
    game->mode = GAME_OVER;
    tinygl_clear();
    if(game->opponent_score == WINNING_SCORE){
        tinygl_text ("DEFEAT! PRESS TO PLAY AGAIN\0");
    } else {
        tinygl_text ("VICTORY! PRESS TO PLAY AGAIN\0");
    }
}


/*Displays the welcome text*/
void display_game_start(void)
{
    tinygl_clear();
    tinygl_text ("WELCOME TO PONG! PRESS TO START\0");
}


/** Displays the current score of your opponent on your screen
 * @param game Game_state_t pointer
 * @param scores List of scores, 0-5 and end of line
*/
void display_scores(Game_state_t* game, char scores[7])
{   
    char buffer[2]; // 2 long buffer for score and EOL
    buffer[0] = scores[game->opponent_score];
    buffer[1] = '\0';
    tinygl_text (buffer);
}
