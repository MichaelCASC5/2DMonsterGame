/**
 * COMPUTER SCIENCE 49900 MAJOR CAPSTONE HUNTER 2024
 *
 * 2D MONSTER GAME
 * CREATED BY ANTON, ANGELA, MICHAEL
 * 01/30/24 Spring Semester
 */

#include "Driver.hpp"

//Xlib thread support
#include <X11/Xlib.h>

/**
 * Main function from which the game is run
 */
int main() {
    //Enable thread support for Xlib
    XInitThreads();

    //Create the driver and start it
    Driver g;
    g.start();
}
