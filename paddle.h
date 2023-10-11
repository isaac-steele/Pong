/** @file paddle.c
    @author K. Lindsay
    @date 9 August 2023
    @brief Paddle support
*/

#ifndef PADDLE_H
#define PADDLE_H

#include "system.h"

typedef struct {
    int left;
    int right;
} Paddle_pos_t;

/* Basic padedle funcitonality*/
Paddle_pos_t paddle_init(void);
Paddle_pos_t paddle_move_left(Paddle_pos_t paddle);
Paddle_pos_t paddle_move_right(Paddle_pos_t paddle);

#endif /* PACER_H*/
