#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "ir_uart.h"

#include "paddle.h"
#include "ball.h"

#define INITIAL_SCORE 0
#define START_MODE 0
#define PLAY_MODE 1


/* game state, contains all key information about current game state*/
typedef struct {
    char score;
    char opponent_score;
    uint8_t mode; //game modes: SETUP==0, PLAY == 1, DISPLAY_SCORE == 2 
} Game_state_t;



#define PACER_RATE 1000
/* Initialize tinygl, system, navswitch and pacer
*/
void initialize(void) 
{
    system_init();
    pacer_init(PACER_RATE);
    tinygl_init(PACER_RATE);
    navswitch_init();
    ir_uart_init();

}

void paddles(Paddle_t* paddle, ball_state_t* ball, Game_state_t* game)
{
    navswitch_update();
    tinygl_update();
    if(navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        *paddle = paddle_move_right(*paddle);
    }
    if(navswitch_push_event_p (NAVSWITCH_NORTH)) {
        *paddle = paddle_move_left(*paddle);
    }
}

void do_ball_stuff(Paddle_t* paddle, ball_state_t* ball, Game_state_t* game)
{
    tinygl_draw_point(ball->pos, 0);
    *ball = ball_update(*ball, *paddle);
    tinygl_draw_point(ball->pos, 1);
}

int main (void)
{
    initialize();
    Paddle_t paddle;
    paddle = paddle_init();
    ball_state_t ball = ball_init (1,5, DIR_SE);

    Game_state_t game;
    game.score = INITIAL_SCORE;
    game.opponent_score = INITIAL_SCORE;
    game.mode = 0;


    uint32_t tick = 0;

    while(1) {
        pacer_wait();
        tinygl_update();
        tick++;
        switch(game.mode) {
            case START_MODE:
                tinygl_draw_point(ball.pos, 1);
                game.mode = 1;
                break;
            case PLAY_MODE:
                paddles(&paddle, &ball, &game);
                if(tick >= 200) {
                    do_ball_stuff(&paddle, &ball, &game);
                    tick = 0;
                }
                break;
        }

    }

}
