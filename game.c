#include "system.h"
#include "pacer.h"
#include "tinygl.h"

#include "paddle.h"
#include "ball.h"
    

#define LOOP_RATE 1000
int main (void)
{

    system_init ();

    ball_state_t ball = ball_init (3,3, DIR_E);
    
    tinygl_init(LOOP_RATE);
    pacer_init(LOOP_RATE);
    

    paddle_init();

    while (1)
    {
        pacer_wait();
        tinygl_update();
    }
}
