#include <stdio.h>
#include <stdlib.h>

#include <SDL3_image/SDL_image.h>

#include "jsi.h"
#include "keypress.h"
#include "events.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

void create_window(struct app* app) {
    if (!SDL_Init(SDL_INIT_VIDEO))
        print_error_cleanup_and_exit(app);

    app->window = SDL_CreateWindow(app->name, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!app->window)
        print_error_cleanup_and_exit(app);

    app->renderer = SDL_CreateRenderer(app->window, NULL);
    if (!app->renderer)
        print_error_cleanup_and_exit(app);
}

void load_image(struct app* app, const char* image_path) {
    SDL_Surface* surface = IMG_Load(image_path);
    if (!surface)
        print_error_cleanup_and_exit(app);

    app->texture = SDL_CreateTextureFromSurface(app->renderer, surface);
    SDL_DestroySurface(surface);
    if (!app->texture)
        print_error_cleanup_and_exit(app);
}

void run(struct app* app) {
    SDL_Event event;
    app->running = true;
    while (app->running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                app->running = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                handle_keypress(app, &event.key);
            }
        }

        apply_image_transformation(app); // inverse, turn, ...
        apply_app_transformation(app);   // fullscreen, ...
        update_renderer(app);
    }
}

void update_renderer(struct app* app) {
    SDL_RenderPresent(app->renderer);
    SDL_Delay(16);
}

void handle_keypress(struct app* app, SDL_KeyboardEvent* key) {
    switch (key->key) {
    case SDLK_Q:
        if (!special_key_pressed(key->mod)) // if <q> has been pressed
            app->running = false;
        break;
    case SDLK_ESCAPE:
        if (!special_key_pressed(key->mod)) // if <esc> has been pressed
            app->running = false;
        break;
    case SDLK_I:
        if (!special_key_pressed(key->mod)) { // if <i> has been pressed
            switch (app->image_state) {
            case NORMAL:
                app->image_state = INVERSE;
                break;
            case TURN:
                app->image_state |= INVERSE;
                break;
            default: // app->image_state = INVERESE or app->image_state = INVERSE | ...
                app->image_state &= ~INVERSE; // remove INVERSE
                break;
            }
        }
        break;
    case SDLK_T:
        if (!special_key_pressed(key->mod)) { // if <t> has been pressed
            switch (app->image_state) {
            case NORMAL:
                app->image_state = TURN;
                break;
            case INVERSE:
                app->image_state |= TURN;
                break;
            default:                       // app->image_state = TURN or app->image_state = TURN | ...
                app->image_state &= ~TURN; // remove TURN
                break;
            }
        }
        break;
    case SDLK_R:
        app->image_state = NORMAL;
        break;
    case SDLK_F:
        if (!special_key_pressed(key->mod)) // if <f> has been pressed
            app->is_fullscreen = (app->is_fullscreen == true) ? false : true;
        break;
    default:
        break;
    }
}

void apply_image_transformation(struct app* app) {
    if (app->image_state == (INVERSE | TURN))
        inverse_and_turn_image(app);
    else if (app->image_state == INVERSE)
        inverse_image(app);
    else if (app->image_state == TURN)
        turn_image(app);
    else // app->image_state = NORMAL
        reload_image(app);
}

void apply_app_transformation(struct app* app) {
    SDL_SetWindowFullscreen(app->window, app->is_fullscreen);
}

void cleanup(struct app* app) {
    if (app->texture) {
        SDL_DestroyTexture(app->texture);
        app->texture = NULL;
    }
    if (app->renderer) {
        SDL_DestroyRenderer(app->renderer);
        app->renderer = NULL;
    }
    if (app->window) {
        SDL_DestroyWindow(app->window);
        app->window = NULL;
    }
    SDL_Quit();
}

void print_error_cleanup_and_exit(struct app* app) {
    fprintf(stderr, "jsi: %s.\n", SDL_GetError());
    cleanup(app);
    exit(EXIT_FAILURE);
}

void print_usage(void) {
    fputs("Usage: jsi <image_path>.\n", stdout);
}
