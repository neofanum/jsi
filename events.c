#include "events.h"

void reload_image(struct app* app) {
    SDL_RenderTexture(app->renderer, app->texture, NULL, NULL);
}

void inverse_image(struct app* app) {
    SDL_RenderTextureRotated(app->renderer, app->texture, NULL, NULL, 0.0, NULL, SDL_FLIP_VERTICAL);
}

void turn_image(struct app* app) {
    SDL_RenderTextureRotated(app->renderer, app->texture, NULL, NULL, 0.0, NULL, SDL_FLIP_HORIZONTAL);
}

void inverse_and_turn_image(struct app* app) {
    SDL_RenderTextureRotated(app->renderer, app->texture, NULL, NULL, 0.0, NULL,
                             SDL_FLIP_VERTICAL | SDL_FLIP_HORIZONTAL);
}
