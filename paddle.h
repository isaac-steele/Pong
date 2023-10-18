/** @file paddle.h
    @author Isaac Steele ist46, Kade Lindsay kli107
    @date 18 October 2023
    @brief Paddle movement and initialization
*/

#ifndef PADDLE_H
#define PADDLE_H

#include "system.h"
#include "navswitch.h"

/*Endpoints of the paddle*/
typedef struct {
    int left;  
    int right;
} Paddle_t;

/*Initialize the paddle to be at the center of the players side of the display*/
Paddle_t paddle_init(void);
/** Shifts the paddle to the left one pixel*/
Paddle_t paddle_move_left(Paddle_t paddle);
/*Shifts the paddle to the right one pixel*/
Paddle_t paddle_move_right(Paddle_t paddle);
/*Function to move the paddle based on navswitch input*/
void move_paddles(Paddle_t* paddle);

#endif /* PADDLE_H*/
