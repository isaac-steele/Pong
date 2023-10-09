/**
 * @file ball.c
 * @author Isaac Steele, ist46
 * @date 09/10/23
 * @brief Makes a ball that can be used for pong
*/

#include "system.h"
#include "ball.h" 
#include "ir_uart.h"

/** Initialise the state of a ball
    @param xstart x coordinate to start at
    @param ystart y coordinate to start at
    @param dir initial direction
    @return state.  */
ball_state_t ball_init (uint8_t xstart, uint8_t ystart, ball_dir_t dir) 
{

    ball_state_t state;

    state.pos.x = xstart;
    state.pos.y = ystart;
    state.dir = dir;

    return state;
}


/** Update the state of a ball bouncing off the edges of the display
    @param state current state
    @return new state.  */
ball_state_t ball_update (ball_state_t state) 
{
    tinygl_point_t movement[] = {{1, 0}, {1, 1}, {1, -1},
                             {-1, 0}, {-1, -1}, {-1, 1}};

    state.pos.x += movement[state.dir].x;
    state.pos.y += movement[state.dir].y;
    
    if (state.pos.y > TINYGL_HEIGHT - 1 || state.pos.y < 0)
    {
        ball_dir_t newdir[] = {DIR_E, DIR_SE, DIR_NE,
                                DIR_W, DIR_NW, DIR_SW};
        state.pos.y -= 2 * movement[state.dir].y;
        state.dir = newdir[state.dir];
    }
    
    if (state.pos.x < 0)
    {
        send_ball(state);
    }

    if (state.pos.x > TINYGL_WIDTH - 1)    
    {
        //TODO: this is where it hits the paddle so need to check y position against paddle position.
    }

    return state;

}


/** Sends the current position of the ball to another device
 * @param state the state of the ball
*/
void send_ball (ball_state_t state)
{
    ir_uart_putc(state.pos.y);
}

/** Receives the current state of the ball 
 * @return state
*/
ball_state_t receive_ball(void) 
{

    uint8_t yposition = ir_uart_getc ();
    ball_state_t state;

    state.pos.x = 0;
    state.pos.y = yposition;
    state.dir = DIR_W;

    return state;
}


/** Turns off the ball
 *
*/
void turn_off_ball(void)
{
    // Calling this could clear the paddle as well
    tinygl_clear();
}

