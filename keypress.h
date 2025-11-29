#ifndef KEYPRESS_H
#define KEYPRESS_H

#include <SDL3/SDL.h>

bool shift_pressed(SDL_Keymod mod);
bool ctrl_pressed(SDL_Keymod mod);
bool alt_pressed(SDL_Keymod mod);
bool special_key_pressed(SDL_Keymod mod);

#endif // KEYPRESS_H
