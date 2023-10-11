/**
 * @file ball.c
 * @author Isaac Steele, ist46
 * @date 09/10/23
 * @brief Makes a ball that can be used for pong
*/

#include "system.h"
#include "ball.h" 
#include "ir_uart.h"
#include "paddle.h"

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
ball_state_t ball_update (ball_state_t state, Paddle_pos_t paddle) 
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
        if(state.pos.y <= paddle.right && state.pos.y >= paddle.left) {
            ball_dir_t newdir[] = {DIR_W, DIR_NW, DIR_SW, 
                                   DIR_E, DIR_SE, DIR_NE};
            state.pos.x -= 2 * movement[state.dir].x;
            state.dir = newdir[state.dir];
        } else {
            //TODO: game over
        }
    }

    return state;

}


/** Sends the current position of the ball to another device
 * @param state the state of the ball
*/
void send_ball (ball_state_t state)
{
    ir_uart_putc(state.pos.y);

    ir_uart_putc(send_dir(state.dir));
}

/** Receives the current state of the ball 
 * @return state
*/
ball_state_t receive_ball(void) 
{  
    ball_state_t state;

    if (ir_uart_read_ready_p ()) {
        uint8_t yposition = ir_uart_getc ();
        uint8_t dir = ir_uart_getc ();

        state.pos.x = 0;
        state.pos.y = yposition;
        state.dir = get_dir(dir);

        
    }

    return state;

   
}


/** Turns off the ball
 *@param state the state of the ball
*/
void turn_off_ball(ball_state_t state)
{
    tinygl_draw_point(state.pos, 0);
}


/**
 * Gets the ball_dir to send
 * @param dir the current direction of the ball
 * @return ball direction
*/
uint8_t send_dir(ball_dir_t dir)
{
    uint8_t new_dir = 0;

    switch(dir) 
    {
        case DIR_W:
            new_dir = 0;
            break;
        case DIR_SW:
            new_dir = 1;
            break;
        case DIR_NW:
            new_dir = 2;
            break;
        default:
            break;
    }

    return new_dir;
}

/**
 * Gets the ball dir
 * @param dir_number the directon number
 * @return ball direction
*/
ball_dir_t get_dir(uint8_t dir_number)
{
    ball_dir_t new_dir = 0;

    switch(dir_number) 
    {
        case 0:
            new_dir = DIR_E;
            break;
        case 1:
            new_dir = DIR_SE;
            break;
        case 2:
            new_dir = DIR_NE;
            break;
        default:
            break;
    }

    return new_dir;
}

