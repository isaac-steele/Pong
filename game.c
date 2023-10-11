#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"

#include "paddle.h"
#include "ball.h"
    

#define LOOP_RATE 1000
int main (void)
{

    system_init ();

    ball_state_t ball = ball_init (3,3, DIR_SW);
    
    tinygl_init(LOOP_RATE);
    pacer_init(LOOP_RATE);
    
    Paddle_pos_t paddle = paddle_init();
    navswitch_init();

    int tick = 0;

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

        tinygl_draw_point(ball.pos, 1);

        tick++;

        if (tick >= 40) {
            tick = 0;

            tinygl_draw_point(ball.pos, 0);

            ball = ball_update(ball, paddle);

            tinygl_draw_point(ball.pos, 1);
        }
    }
}
