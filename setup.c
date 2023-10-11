/** @file paddle.c
    @author K. Lindsay
    @date 9 August 2023
    @brief Initialize game state
*/
#include "system.h"
#include "tinygl.h"
#include "setup.h"

/* Setup display to select player 1 or 2
*/

/* Select your player
 * @param Player_info_t player
*/
void selectPlayer(Player_info_t player) {
    // select what player you are
    char character = 1;
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        character += 1;
    }
}