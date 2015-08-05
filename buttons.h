#ifndef BUTTONS__H
#define BUTTONS__H

// persist the last known state of the buttons
volatile extern bool button_state[ 6 ];
volatile extern bool button_rising[ 6 ];
volatile extern bool button_falling[ 6 ];
volatile extern bool button_pushed[ 6 ];
volatile extern bool button_released[ 6 ];

bool set_button_state( int button, bool value );

void reset_button_states(); // call this function after checking rising/falling checks to get correct data in next iteration

void print_button_states();

#endif