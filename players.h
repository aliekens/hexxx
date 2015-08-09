#ifndef PLAYERS__H
#define PLAYERS__H

#include "hexxx.h"

#define PLAYERS 3
extern int player_position[PLAYERS];
extern bool player_human[PLAYERS];
extern bool player_alive[PLAYERS];
extern ws2811_led_t player_color[PLAYERS];

void invite_players();

#endif