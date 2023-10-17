/** @file paddle.c
    @author Isaac Steele ist46, Kade Lindsay kli107
    @date 18 October 2023
    @brief Paddle support
*/

#ifndef PADDLE_H
#define PADDLE_H

#include "system.h"

typedef struct {
    int left;
    int right;
} Paddle_t;

/* Basic padedle funcitonality*/
Paddle_t paddle_init(void);
Paddle_t paddle_move_left(Paddle_t paddle);
Paddle_t paddle_move_right(Paddle_t paddle);

#endif /* PACER_H*/
