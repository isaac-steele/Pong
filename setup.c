/** @file paddle.c
    @author K. Lindsay
    @date 9 August 2023
    @brief Initialize game state
*/

#include "setup.h"

/* Setup display to select player 1 or 2
*/

/* Select your player
 * @param Player_info_t player
*/

void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}