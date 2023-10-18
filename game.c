/**
 * @file game.c
 * @author Isaac Steele ist46, Kade Lindsay kli107
 * @date 18 October 2023
 * @brief A simple pong game that has a scoring system of first to 5 wins
*/


#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "led.h"
#include "../fonts/font5x7_1.h"

#include "paddle.h"
#include "ball.h"
#include "game_state.h"

#define INITIAL_SCORE  0
#define START_MODE 0
#define PLAY_MODE 1
#define DISPLAY_SCORE 2
#define GAME_OVER 10
#define PACER_RATE 1000
#define MESSAGE_RATE 10
#define BALL_RATE 200
#define START_X 0
#define START_Y 3
#define START_DIR DIR_E
#define START_GAME 1

/* Initialize all relevant functions such as system, pacer, tinygl, navswitch and IR*/
void initialize(void) 
{
    system_init();
    pacer_init(PACER_RATE);
    tinygl_init(PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    navswitch_init();
    ir_uart_init();

}

/** 
 * Resets the paddle and ball to initial positions
 * @param game pointer to the current state of the game
 * @param paddle pointer to the current paddle
 * @param ball pointer to the current state of the ball
*/
void reset_paddle_and_ball(Game_state_t* game, Paddle_t* paddle, ball_state_t* ball)
{
    *paddle = paddle_init();
    *ball = ball_init (START_X,START_Y, START_DIR);
    tinygl_draw_point(ball->position, 1);
    game->has_ball = true;
    game->mode = PLAY_MODE;
}

/** Updates the ball movement and checks if a point has been scored
 * @param paddle pointer to the current paddle
 * @param ball pointer to the current state of the ball
 * @param game pointer to the current state of the game
*/
void update_ball_movement(Paddle_t* paddle, ball_state_t* ball, Game_state_t* game)
{   
    if(game->has_ball){
        tinygl_draw_point(ball->position, 0);
        *ball = ball_update(*ball, *paddle);
        if(ball->position.x == POINT_SCORED ) {
            game->opponent_score++;
            if(game->opponent_score == WINNING_SCORE) {
                ir_uart_putc(GAME_OVER);
                game_over(game);
            } else {
                tinygl_clear();
                game->mode = DISPLAY_SCORE;
            }
        }
        else if(ball->position.x < MIN_X_POSITION) {
            game->has_ball = false;
        } else {
            tinygl_draw_point(ball->position, 1);
        }
        
    }
}



/** Starts the game upon navswitch push, or upon recieving navswitch push from opponent
 * @param paddle pointer to the current paddle
 * @param ball pointer to the current state of the ball
 * @param game pointer to the current state of the game
*/

void start_game(Paddle_t* paddle, ball_state_t* ball, Game_state_t* game) 
{
    if(navswitch_push_event_p (NAVSWITCH_PUSH)){
        //TRANSMIT READY TO PLAY
        ir_uart_putc(START_GAME);   
        reset_paddle_and_ball(game, paddle, ball);
        game->mode = PLAY_MODE;
    }

    if(ir_uart_read_ready_p()) {
        //RECIEVE READY TO PLAY 
        char character = ir_uart_getc();
        if(character == START_GAME) {
            game->mode = PLAY_MODE;
            *paddle = paddle_init();
            game->has_ball = false;
        }

    }
}

/** Check for IR transmission
 * if the first character recieved is not game over, recieve direction too
 * @param game pointer to the current state of the game
 * @param ball pointer to the current state of the ball
*/
void check_for_transmission(Game_state_t* game, ball_state_t* ball)
{
    uint8_t character = NO_CHARACTER;
    uint8_t dir = NO_DIRECTION;
    if(ir_uart_read_ready_p()){
        character = ir_uart_getc();
        if(character == GAME_OVER){
            game_over(game);
        } else {
            dir = ir_uart_getc();
            if(check_ball_received(ball, character, dir)){
                tinygl_draw_point(ball->position, 1);
                game->has_ball = true;
            }
        }
    }
}


int main (void)
{
    initialize();

    Paddle_t paddle;
    ball_state_t ball;
    Game_state_t game;

    game.score = INITIAL_SCORE;
    game.opponent_score = INITIAL_SCORE;
    game.mode = START_MODE;
    game.has_ball = false;

    led_init();
    led_set(LED1, 0);

    uint32_t tick = 0;
    char scores[7] = "012345\0";

    display_game_start();
    while(1) {
        pacer_wait();
        tinygl_update();
        navswitch_update();
        tick++;

        switch(game.mode) {
            case START_MODE:
                start_game(&paddle, &ball, &game);
                break;
            case PLAY_MODE:
                move_paddles(&paddle);
                if(!(game.has_ball)){
                    check_for_transmission(&game, &ball);
                } 
                if(tick >= BALL_RATE) {
                    update_ball_movement(&paddle, &ball, &game);
                    tick = 0;
                }
                break;
            case DISPLAY_SCORE:
                if(navswitch_push_event_p (NAVSWITCH_PUSH)){
                    tinygl_clear();
                    reset_paddle_and_ball(&game, &paddle, &ball);
                } else {
                    display_scores(&game, scores);
                }
                break;
            case GAME_OVER:
                if(navswitch_push_event_p (NAVSWITCH_PUSH)){
                    tinygl_clear();
                    game.mode = START_MODE;
                    display_game_start();
                }
                break;
        }

    }   
}
