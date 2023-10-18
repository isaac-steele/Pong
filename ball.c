/**
 * @file ball.c
 * @author Isaac Steele ist46, Kade Lindsay kli107
 * @date 18 October 2023
 * @brief Makes a ball that can be used for pong
*/

#include "system.h"
#include "ball.h" 
#include "ir_uart.h"
#include "paddle.h"

/**
 * An array of coordinates which corresponds to ball_dir_t that
 * is used to move the ball
*/
tinygl_point_t movement[] = {
        {1, 0}, 
        {1, 1}, 
        {1, -1},
        {-1, 0}, 
        {-1, -1}, 
        {-1, 1}
    };

/** Initialise the position and direction of the ball
    @param xPosition the position on the x axis to start at
    @param yPosition the position on the y axis to start at
    @param direction the initial direction
    @return the intialised ball.  */
ball_state_t ball_init (uint8_t xPosition, uint8_t yPosition, ball_dir_t direction) 
{

    ball_state_t ball = {
        .position.x = xPosition,
        .position.y = yPosition,
        .direction = direction
    };

    return ball;
}


/** Updates the position and direction of a ball based on whether it hits the paddle,
 * a wall, or needs to get sent to the other player
    @param ball current position and direction of the ball
    @param paddle the current paddle
    @return new position and direction of the ball.  */
ball_state_t ball_update (ball_state_t ball, Paddle_t paddle) 
{
    move_ball(&ball);
    
    if (ball.position.y > MAX_Y_POSITON || ball.position.y < MIN_Y_POSITION) {

        update_ball_y_wall(&ball);
    }
    
    if (ball.position.x < MIN_X_POSITION) {

        send_ball(ball);
        turn_off_ball(ball);
    }

    if (ball.position.x > MAX_X_POSITION) {

        turn_off_ball(ball);
        ball.position.x = POINT_SCORED;

    } else if (ball.position.x > MAX_X_PADDLE_POSITION) {
        
        update_ball_paddle(&ball, paddle);
        
    }

    return ball;

}

/**
 * Updates the ball position and direction if it hits a wall on the y axis
 * @param ball the current position and direction of the ball
 * 
*/
void update_ball_y_wall(ball_state_t* ball)
{
    ball_dir_t updatedDirection[] = {
            DIR_E, 
            DIR_SE, 
            DIR_NE, 
            DIR_W, 
            DIR_NW, 
            DIR_SW
        };
    ball->position.y -= 2 * movement[ball->direction].y;
    ball->direction = updatedDirection[ball->direction];
}

/**
 * Moves the ball 
 * @param ball a pointer to the current position and direction of the ball
*/
void move_ball(ball_state_t* ball)
{
    ball->position.x += movement[ball->direction].x;
    ball->position.y += movement[ball->direction].y;
}

/**
 * Updates the ball position if it has the chance to hit the paddle
 * @param ball a pointer to the current position and direction of the ball
 * @param paddle the current paddle
*/
void update_ball_paddle(ball_state_t* ball, Paddle_t paddle)
{
    if(ball->position.y <= paddle.left && ball->position.y >= paddle.right) {
        ball_dir_t updatedDirection[] = {
            DIR_W, 
            DIR_NW, 
            DIR_SW, 
            DIR_E, 
            DIR_SE, 
            DIR_NE
        };
        ball->position.x -= 2 * movement[ball->direction].x;           
        if(ball->position.y == paddle.left) {
            ball->position.y += 1;
            ball->direction = DIR_NW;
        } else if (ball->position.y == paddle.right) {
            ball->position.y -= 1;
            ball->direction = DIR_SW;
        } else {
            ball->direction = updatedDirection[ball->direction];
        }
            
    } 
}




/** Sends the current position and direction of the ball to another device
 * @param ball the ball
*/
void send_ball (ball_state_t ball)
{
    ir_uart_putc(ball.position.y);

    ir_uart_putc(send_dir(ball.direction));
}


/**
 * Checks if a ball is received or not
 * @param ball the current position and direction of the ball
 * @param yPos the current yPosition of the ball
 * @param direction the current direction of the ball
 * @return num which is 1 or 0 depnidng if a ball is received
*/
uint8_t check_ball_received(ball_state_t* ball, uint8_t yPos, uint8_t direction)
{
    //*ball = receive_ball(character, direction);
    if(yPos == NO_CHARACTER && direction == NO_DIRECTION) {
        return 0;
    } else {
        *ball = ball_init(0, convert_ypos(yPos), direction);
        return 1;
    }
}


/** Turns off the ball
 *@param ball the ball
*/
void turn_off_ball(ball_state_t ball)
{
    tinygl_draw_point(ball.position, 0);
}


/**
 * Gets the ball direction to send
 * @param direction the current direction of the ball
 * @return ball direction
*/
uint8_t send_dir(ball_dir_t direction)
{
    uint8_t new_dir = DIR_E;

    switch(direction) 
    {
        case DIR_W:
            new_dir = DIR_E;
            break;
        case DIR_SW:
            new_dir = DIR_NE;
            break;
        case DIR_NW:
            new_dir = DIR_SE;
            break;
        default:
            break;
    }

    return new_dir;
}

/**
 * Converts the y position
 * @param yPos the y position
 * @return the updated y position
*/
uint8_t convert_ypos(uint8_t yPos)
{
    switch(yPos) {
        case 0:
            return 6;
        case 1:
            return 5;
        case 2:
            return 4;
        case 3:
            return 3;
        case 4:
            return 2;
        case 5:
            return 1;
        case 6:
            return 0;
        default:
            return 0;
    }
}

