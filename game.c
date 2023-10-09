#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"

#include "paddle.h"
    

#define LOOP_RATE 1000
int main (void)
{

    system_init ();

    tinygl_init(LOOP_RATE);
    pacer_init(LOOP_RATE);
    paddle_init();
    navswitch_init();

    while (1)
    {
        pacer_wait();
        tinygl_update();
        navswitch_update();

        if(navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            paddle_move_right();
        }
        if(navswitch_push_event_p (NAVSWITCH_NORTH)) {
            paddle_move_left();
        }
    }
}
