/**
 * @file ball.h
 * @author Isaac Steele ist46, Kade Lindsay kli107
 * @date 18 October 2023
 * @brief Makes a ball that can be used for pong
*/

#ifndef BALL_H
#define BALL_H

#include "tinygl.h"
#include "paddle.h"

#define POINT_SCORED -100

/** Compass direction of ball.  */
typedef enum dir {DIR_E, DIR_NE, DIR_SE,
                  DIR_W, DIR_SW, DIR_NW} ball_dir_t;


/** Structure defining state of ball.  */
typedef struct state {tinygl_point_t pos; ball_dir_t dir;} ball_state_t;


/** Update the state of a ball bouncing off the edges of the display
    @param state current state
    @param paddle the paddle
    @return new state.  */
ball_state_t ball_update (ball_state_t state, Paddle_t paddle);


/** Initialise the state of a ball
    @param xstart x coordinate to start at
    @param ystart y coordinate to start at
    @param dir initial direction
    @return state.  */
ball_state_t ball_init (uint8_t xstart, uint8_t ystart, ball_dir_t dir);

/** Sends the current position of the ball to another device
 * @param state the state of the ball
*/
void send_ball (ball_state_t state);

// /** Receives the current state of the ball 
//  * @return state
// */
// ball_state_t receive_ball(uint8_t y_pos);

/** Turns off the ball
 *@param state the state of the ball
*/
void turn_off_ball(ball_state_t state);

/**
 * Gets the ball_dir to send
 * @param dir the current direction of the ball
 * @return ball direction
*/
uint8_t send_dir(ball_dir_t dir);

/**
 * Gets the ball dir
 * @param dir_number the directon number
 * @return ball direction
*/
ball_dir_t get_dir(uint8_t dir_number);


/**
 * Checks if a ball is received or not
 * @return num whihc is 1 or 0 depnidng if a ball is received
*/
uint8_t check_ball_received(ball_state_t* state, uint8_t y_pos, uint8_t dir);

/**
 * Converts the y position
 * @param y_pos the y position
 * @return the updated y position
*/
uint8_t convert_ypos(uint8_t ypos);




#endif /* BALL_H */