#include "system.h"
#include "pacer.h"
#include "tinygl.h"

#include "paddle.h"
    

#define LOOP_RATE 1000
int main (void)
{

    system_init ();
    
    tinygl_init(LOOP_RATE);
    pacer_init(LOOP_RATE);

    paddle_init();

    while (1)
    {
        pacer_wait();
        tinygl_update();
    }
}
