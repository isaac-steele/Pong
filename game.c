#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "led.h"
#include "../fonts/font5x7_1.h"

#include "paddle.h"
#include "ball.h"
#include "setup.h"

#define INITIAL_SCORE  0
#define START_MODE 0
#define PLAY_MODE 1
#define DISPLAY_SCORE 2
#define GAME_OVER 10


/* game state, contains all key information about current game state*/
typedef struct {
    uint8_t score;
    uint8_t opponent_score;
    uint8_t mode; //game modes: SETUP==0, PLAY == 1, DISPLAY_SCORE == 2
    bool has_ball;
} Game_state_t;



#define PACER_RATE 1000
#define MESSAGE_RATE 10
/* Initialize tinygl, system, navswitch and pacer
*/
void initialize(void) 
{
    system_init();
    pacer_init(PACER_RATE);
    tinygl_init(PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    navswitch_init();
    ir_uart_init();

}
/*Controls movement of the paddles
    @param 
*/
void paddles(Paddle_t* paddle)
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

void make_game_over(Game_state_t* game)
{
    game->mode = GAME_OVER;
    tinygl_clear();
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text ("GAME OVER! PRESS TO PLAY AGAIN ");
}

void do_ball_stuff(Paddle_t* paddle, ball_state_t* ball, Game_state_t* game)
{   

    if(game->has_ball){
        tinygl_draw_point(ball->pos, 0);
        *ball = ball_update(*ball, *paddle);
        if(ball->pos.x == POINT_SCORED ) {
            game->opponent_score++;
            if(game->opponent_score == 5) {
                ir_uart_putc(GAME_OVER);
                make_game_over(game);
            } else {
                tinygl_clear();
                game->mode = DISPLAY_SCORE;
            }
        }
        else if(ball->pos.x < 0) {
            game->has_ball = false;
        } else {
            tinygl_draw_point(ball->pos, 1);
        }
        
    }
}





void start_game(Paddle_t* paddle, ball_state_t* ball, Game_state_t* game) 
{
    tinygl_update();
    navswitch_update();

    if(navswitch_push_event_p (NAVSWITCH_PUSH)){
        //TRANSMIT READY TO PLAY
        ir_uart_putc(1);   
        game->has_ball = true;
        game->mode = PLAY_MODE;
        *paddle = paddle_init();
        *ball = ball_init (1,5, DIR_SE);
        tinygl_draw_point(ball->pos, 1);
        game->opponent_score = 0;
    }

    if(ir_uart_read_ready_p()) {
        //RECIEVE READY TO PLAY 
        char character = ir_uart_getc();
        if(character == 1) {
            game->mode = PLAY_MODE;
            *paddle = paddle_init();
            game->has_ball = false;
            game->opponent_score = 0;
        }

    }
}

void check_for_transmission(Game_state_t* game, ball_state_t* ball)
{
    uint8_t character = 0;
    uint8_t dir = 3;
    if(ir_uart_read_ready_p()){
        character = ir_uart_getc();
        if(character == GAME_OVER){
            make_game_over(game);
        } else {
            dir = ir_uart_getc();
            if(check_ball_received(ball, character, dir)){
                tinygl_draw_point(ball->pos, 1);
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

    led_init();
    led_set(LED1, 0);
    uint32_t tick = 0;
    char scores[6] = "012345";
    while(1) {
        pacer_wait();
        tinygl_update();
        tick++;

        switch(game.mode) {
            case START_MODE:
                start_game(&paddle, &ball, &game);
                break;
            case PLAY_MODE:
                paddles(&paddle);
                check_for_transmission(&game, &ball);
                // if(!(game.has_ball)){
                //     check_for_transmission(&game, &ball);
                // }
                if(tick >= 200) {
                    do_ball_stuff(&paddle, &ball, &game);
                    tick = 0;
                }
                break;
            case DISPLAY_SCORE:
                navswitch_update ();
                if(navswitch_push_event_p (NAVSWITCH_PUSH)){
                    tinygl_clear();
                    game.mode = PLAY_MODE;
                    paddle = paddle_init();
                    ball = ball_init (1,5, DIR_SE);
                    tinygl_draw_point(ball.pos, 1);
                    game.has_ball = true;
                } else {
                    char buffer[2];
                    buffer[0] = scores[game.opponent_score];
                    buffer[1] = '\0';
                    tinygl_text (buffer);
                }
                break;
            case GAME_OVER:
                navswitch_update();
                if(navswitch_push_event_p (NAVSWITCH_PUSH)){
                    tinygl_clear();
                    game.mode = START_MODE;
                }
                break;
        }

    }   
}
