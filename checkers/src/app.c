#include "app.h"

typedef struct App {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* event;
} App;

static App app;

int App_Init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("%s\n", SDL_GetError());
		return -1;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0) {
		printf("%s\n", SDL_GetError());
		return -2;
	}

	app.window = SDL_CreateWindow(APP_WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (app.window == NULL) {
		printf("%s\n", SDL_GetError());
		return -3;
	}

	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
	if (app.renderer == NULL) {
		printf("%s\n", SDL_GetError());
		return -4;
	}

	return 0;
}

void App_Destroy() {

	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);

	IMG_Quit();
	SDL_Quit();

}

int App_Menu() {

	bool IS_STATE_RUNNING = true;

	while (IS_STATE_RUNNING) {

		SDL_PollEvent(&app.event);
		SDL_RenderPresent(app.renderer);

	}

	return 0;
}

int App_Game() {
	return 0;
}

int App_GameOver() {
	return 0;
}