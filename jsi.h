#ifndef JSI_H
#define JSI_H

#include <SDL3/SDL.h>

struct app {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    bool is_fullscreen;
    bool running;
    char name[256];

    // image state
    enum {
        NORMAL = 0,       // the image is normal
        INVERSE = 1 << 0, // the image is flip vertically
        TURN = 1 << 1,    // the image is flip horizontally
    } image_state;
};

void create_window(struct app* app);
void load_image(struct app* app, const char* image_path);
void run(struct app* app);
void update_renderer(struct app* app);
void handle_keypress(struct app* app, SDL_KeyboardEvent* key);
void apply_image_transformation(struct app* app);
void apply_app_transformation(struct app* app);
void cleanup(struct app* app);
void print_usage(void);
void print_error_cleanup_and_exit(struct app* app);

#endif // JSI_H
