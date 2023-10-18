/** @file paddle.c
    @author Isaac Steele ist46, Kade Lindsay kli107
    @date 18 October 2023
    @brief Paddle movement and initialization
*/


#include "system.h"
#include "tinygl.h"
#include "pacer.h"
#include "paddle.h"

#define PADDLE_LEFT_BORDER 0
#define PADDLE_RIGHT_BORDER 6
#define PADDLE_COLUMN 4
#define INITIAL_RIGHT 4
#define INITIAL_LEFT 2
/**
 * 
*/

/** Initialize paddle ends and draw a line between these two points
 * @return Paddle_t paddle struct */
Paddle_t paddle_init(void)
{   
    tinygl_clear(); // clear the board before adding the paddle
    Paddle_t paddle;
    paddle.left = INITIAL_RIGHT;
    paddle.right = INITIAL_LEFT;

    tinygl_draw_line (tinygl_point (PADDLE_COLUMN, paddle.left), tinygl_point (PADDLE_COLUMN, paddle.right), 1);
    return paddle;
}

/** Shifts paddle to the left by one pixel
 * @param paddle paddle_t position struct
 * @return updated paddle position
*/
Paddle_t paddle_move_left(Paddle_t paddle)
{
    if(paddle.right > PADDLE_LEFT_BORDER) { // prevents the paddle from moving past the end of the display
        paddle.left -=1;
        paddle.right -=1;
    }
    tinygl_clear(); 
    tinygl_draw_line (tinygl_point (PADDLE_COLUMN, paddle.left), tinygl_point (PADDLE_COLUMN, paddle.right), 1);
    return paddle;
}

/** Shifts the paddle to the right by one pixel
 * @param paddle paddle_t position struct
 * @return updated paddle position
*/
Paddle_t paddle_move_right(Paddle_t paddle)
{
    if(paddle.left < PADDLE_RIGHT_BORDER) {
        paddle.left +=1;
        paddle.right +=1;
    }
    tinygl_clear(); 
    tinygl_draw_line (tinygl_point (PADDLE_COLUMN, paddle.left), tinygl_point (PADDLE_COLUMN, paddle.right), 1);
    return paddle;
}

/** moves the paddle based on navswitch input
 * @param paddle paddle_t position struct
 * 
*/
void move_paddles(Paddle_t* paddle)
{
    if(navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        *paddle = paddle_move_right(*paddle);
    }
    if(navswitch_push_event_p (NAVSWITCH_NORTH)) {
        *paddle = paddle_move_left(*paddle);
    }
}
