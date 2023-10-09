/**
 * @file ball.h
 * @author Isaac Steele, ist46
 * @date 09/10/23
 * @brief Makes a ball that can be used for pong
*/

#ifndef BALL_H
#define BALL_H

#include "tinygl.h"

/** Compass direction of ball.  */
typedef enum dir {DIR_E, DIR_NE, DIR_SE,
                  DIR_W, DIR_SW, DIR_NW} ball_dir_t;


/** Structure defining state of ball.  */
typedef struct state {tinygl_point_t pos; ball_dir_t dir;} ball_state_t;


/** Update the state of a ball bouncing off the edges of the display
    @param state current state
    @return new state.  */
ball_state_t ball_update (ball_state_t state);


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

/** Receives the current state of the ball 
 * @return state
*/
ball_state_t receive_ball(void);

/** Turns off the ball
 *
*/
void turn_off_ball(void);



#endif /* BALL_H */