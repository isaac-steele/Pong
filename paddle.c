/** @file paddle.c
    @author K. Lindsay
    @date 9 August 2023
    @brief Initialize and move the paddle 
*/


#include "system.h"
#include "tinygl.h"
#include "pacer.h"
#include "paddle.h"

/**
 * Initialize paddle ends and draw a line between these two points
 * Points are updated via paddle_move_right and paddle_move_left
*/

/* Initialize the paddle 
 * @return 
*/
Paddle_t paddle_init(void)
{   
    tinygl_clear(); // clear the board before adding the paddle
    Paddle_t paddle;
    paddle.left = 4;
    paddle.right = 2;

    tinygl_draw_line (tinygl_point (4, paddle.left), tinygl_point (4, paddle.right), 1);
    return paddle;
}

/** Shifts paddle to the left by one pixel
 * @param paddle paddle position struct
 * @return updated paddle position
*/
Paddle_t paddle_move_left(Paddle_t paddle)
{
    if(paddle.right > 0) { // prevents the paddle from moving past the end points of the matrix
        paddle.left -=1;
        paddle.right -=1;
    }
    tinygl_clear(); 
    tinygl_draw_line (tinygl_point (4, paddle.left), tinygl_point (4, paddle.right), 1);
    return paddle;
}

/** Identical to paddle_move_left but in opposite direction
 * @param paddle
 * @return updated paddle position
*/
Paddle_t paddle_move_right(Paddle_t paddle)
{
    if(paddle.left < 6) {
        paddle.left +=1;
        paddle.right +=1;
    }
    tinygl_clear(); 
    tinygl_draw_line (tinygl_point (4, paddle.left), tinygl_point (4, paddle.right), 1);
    return paddle;
}
