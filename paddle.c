/** @file paddle.c
    @author K. Lindsay
    @date 9 August 2023
    @brief Initialize and move the paddle 
*/


#include "system.h"
#include "tinygl.h"
#include "pacer.h"

/**
 * Initialize paddle ends and draw a line between these two points
 * Points are updated via paddle_move_right and paddle_move_left
*/
int paddleLeft = 2;
int paddleRight = 4;

/** Initialize the paddle */
void paddle_init(void)
{   
    tinygl_clear(); // clear the board before adding the paddle
    tinygl_draw_line (tinygl_point (4, paddleLeft), tinygl_point (4, paddleRight), 1);
}

/** Shifts paddle to the left by one pixel
*/
void paddle_move_left(void)
{
    if(paddleLeft > 0) { // prevents the paddle from moving past the end points of the matrix
        paddleLeft -=1;
        paddleRight -=1;
    }
    tinygl_clear(); //May be a problem with this, clears board so new paddle does not combine with previous
    tinygl_draw_line (tinygl_point (4, paddleLeft), tinygl_point (4, paddleRight), 1);
}

/** Identical to paddle_move_left but in opposite direction
*/
void paddle_move_right(void)
{
    if(paddleRight < 6) {
        paddleLeft +=1;
        paddleRight +=1;
    }
    tinygl_clear(); 
    tinygl_draw_line (tinygl_point (4, paddleLeft), tinygl_point (4, paddleRight), 1);
}
