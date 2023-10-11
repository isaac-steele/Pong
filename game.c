#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "ir_uart.h"

#include "paddle.h"
#include "ball.h"
    

#define LOOP_RATE 1000
int main (void)
{

    system_init ();

    ball_state_t ball = ball_init (1,5, DIR_SE);
    
    tinygl_init(LOOP_RATE);
    pacer_init(LOOP_RATE);
    ir_uart_init();
    
    Paddle_pos_t paddle = paddle_init();
    navswitch_init();

    int tick = 0;

    tinygl_draw_point(ball.pos, 1);

    while (1)
    {
        pacer_wait();
        tinygl_update();
        navswitch_update();

        if(navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            paddle = paddle_move_right(paddle);
        }
        if(navswitch_push_event_p (NAVSWITCH_NORTH)) {
            paddle = paddle_move_left(paddle);
        }

        //TODO need a revamp of the ir
        // need something to check the send and check the receive

        //ball = receive_ball();

        tick++;

        if (tick >= 200) {
            tick = 0;

            tinygl_draw_point(ball.pos, 0);

            ball = ball_update(ball, paddle);

            tinygl_draw_point(ball.pos, 1);
        }
    }
}
