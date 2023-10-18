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
#define MAX_Y_POSITON TINYGL_HEIGHT - 1
#define MIN_Y_POSITION 0
#define MIN_X_POSITION 0
#define MAX_X_PADDLE_POSITION TINYGL_WIDTH - 2
#define MAX_X_POSITION TINYGL_WIDTH - 1
#define NO_CHARACTER 0
#define NO_DIRECTION DIR_W

/** Has all the possible directions the ball can go */
typedef enum {
    DIR_E, 
    DIR_NE, 
    DIR_SE,
    DIR_W, 
    DIR_SW, 
    DIR_NW
} ball_dir_t;


/** Keeps track of the direction and the position of the ball  */
typedef struct {
    tinygl_point_t position; 
    ball_dir_t direction;
} ball_state_t;


/** Updates the position and direction of a ball based on whether it hits the paddle,
 * a wall, or needs to get sent to the other player
    @param ball current position and direction of the ball
    @param paddle the current paddle
    @return new position and direction of the ball.  */
ball_state_t ball_update (ball_state_t ball, Paddle_t paddle);


/** Initialise the position and direction of the ball
    @param xPosition the position on the x axis to start at
    @param yPosition the position on the y axis to start at
    @param direction the initial direction
    @return the intialised ball.  */
ball_state_t ball_init (uint8_t xPosition, uint8_t yPosition, ball_dir_t direction);

/**
 * Updates the ball position and direction if it hits a wall on the y axis
 * @param ball the current position and direction of the ball
 * 
*/
void update_ball_y_wall(ball_state_t* ball);

/**
 * Moves the ball 
 * @param ball a pointer to the current position and direction of the ball
*/
void move_ball(ball_state_t* ball);

/**
 * Updates the ball position if it has the chance to hit the paddle
 * @param ball a pointer to the current position and direction of the ball
 * @param paddle the current paddle
*/
void update_ball_paddle(ball_state_t* ball, Paddle_t paddle);

/** Sends the current position and direction of the ball to another device
 * @param ball the ball
*/
void send_ball (ball_state_t ball);


/** Turns off the ball
 *@param ball the ball
*/
void turn_off_ball(ball_state_t ball);

/**
 * Gets the ball direction to send
 * @param direction the current direction of the ball
 * @return ball direction
*/
uint8_t send_dir(ball_dir_t direction);


/**
 * Checks if a ball is received or not
 * @param ball the current position and direction of the ball
 * @param yPos the current yPosition of the ball
 * @param direction the current direction of the ball
 * @return num which is 1 or 0 depnidng if a ball is received
*/
uint8_t check_ball_received(ball_state_t* ball, uint8_t yPos, uint8_t direction);

/**
 * Converts the y position
 * @param yPos the y position
 * @return the updated y position
*/
uint8_t convert_ypos(uint8_t yPos);




#endif /* BALL_H */