/** @file paddle.h
    @author Isaac Steele ist46, Kade Lindsay kli107
    @date 18 October 2023
    @brief Paddle movement and initialization
*/

#ifndef PADDLE_H
#define PADDLE_H

#include "system.h"
#include "navswitch.h"

#define PADDLE_LEFT_BORDER 0
#define PADDLE_RIGHT_BORDER 6
#define PADDLE_COLUMN 4
#define INITIAL_RIGHT 4
#define INITIAL_LEFT 2

/*Endpoints of the paddle*/
typedef struct {
    int left;  
    int right;
} Paddle_t;

/** Initialize paddle ends and draw a line between these two points
 * @return an initialized paddle */
Paddle_t paddle_init(void);

/** Shifts paddle to the left by one pixel
 * @param paddle the current paddle
 * @return updated paddle position
*/
Paddle_t paddle_move_left(Paddle_t paddle);

/** Shifts the paddle to the right by one pixel
 * @param paddle the current paddle
 * @return updated paddle position
*/
Paddle_t paddle_move_right(Paddle_t paddle);

/** Moves the paddle based on navswitch input
 * @param paddle pointer to the current paddle
 */
void move_paddles(Paddle_t* paddle);

#endif /* PADDLE_H*/
