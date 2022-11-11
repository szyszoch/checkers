#include "app.h"

enum TEXTURES {
	TEXTURE_WHITE_CHECKER,
	TEXTURE_BLACK_CHECKER,
	TEXTURE_WHITE_KING_CHECKER,
	TEXTURE_BLACK_KING_CHECKER,
	TEXTURE_BOARD,
	TEXTURE_SELECT,
	TEXTURES_COUNT
};

typedef struct App {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* event;
	SDL_Texture* texture[TEXTURES_COUNT];
} App;

static App app;

int App_Init() {

	// Initializing libraries
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("%s\n", SDL_GetError());
		return -1;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0) {
		printf("%s\n", SDL_GetError());
		return -2;
	}

	// Creating window
	app.window = SDL_CreateWindow(APP_WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (app.window == NULL) {
		printf("%s\n", SDL_GetError());
		return -3;
	}

	// Creating renderer
	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
	if (app.renderer == NULL) {
		printf("%s\n", SDL_GetError());
		return -4;
	}

	// Loading textures
	app.texture[TEXTURE_WHITE_CHECKER] = IMG_LoadTexture(app.renderer, "img/white_checker.png");
	app.texture[TEXTURE_BLACK_CHECKER] = IMG_LoadTexture(app.renderer, "img/black_checker.png");
	app.texture[TEXTURE_WHITE_KING_CHECKER] = IMG_LoadTexture(app.renderer, "img/white_king_checker.png");
	app.texture[TEXTURE_BLACK_KING_CHECKER] = IMG_LoadTexture(app.renderer, "img/black_king_checker.png");
	app.texture[TEXTURE_BOARD] = IMG_LoadTexture(app.renderer, "img/board.png");
	app.texture[TEXTURE_SELECT] = IMG_LoadTexture(app.renderer, "img/select.png");

	for (int i = 0; i < TEXTURES_COUNT; i++) {
		if (app.texture[i] == NULL) {
			printf("%s\n", SDL_GetError());
			return -5;
		}
	}

	return 0;
}

void App_Destroy() {

	for (int i = 0; i < TEXTURES_COUNT; i++) {
		SDL_DestroyTexture(app.texture[i]);
	}

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

