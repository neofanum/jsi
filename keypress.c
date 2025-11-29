#include "keypress.h"

bool shift_pressed(SDL_Keymod mod) {
    return mod & SDL_KMOD_SHIFT;
}

bool ctrl_pressed(SDL_Keymod mod) {
    return mod & SDL_KMOD_CTRL;
}

bool alt_pressed(SDL_Keymod mod) {
    return mod & SDL_KMOD_ALT;
}

bool special_key_pressed(SDL_Keymod mod) {
    return shift_pressed(mod) || ctrl_pressed(mod) || alt_pressed(mod);
}
