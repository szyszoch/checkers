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
	SDL_Event event;
	SDL_Texture* texture[TEXTURES_COUNT];
} App;

static App app;

// ===================

void App_DrawBoard();

// ===================

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

	BD_Load();
	bool IS_STATE_RUNNING = true;

	while (IS_STATE_RUNNING) {

		SDL_RenderClear(app.renderer);
		SDL_PollEvent(&app.event);
		App_DrawBoard();
		SDL_RenderPresent(app.renderer);


	}

	return 0;
}

int App_GameOver() {
	return 0;
}

// ===================

void App_DrawBoard() {

	SDL_Rect src, dst;
	
	// Board
	src.x = 0; src.y = 0; src.w = 800; src.h = 800;
	dst.x = 0; dst.y = 0; dst.w = 800; dst.h = 800;
	SDL_RenderCopy(app.renderer, app.texture[TEXTURE_BOARD], &src, &dst);
	
	// Checkers
	src.x = 0; src.y = 0; src.w = 100; src.h = 100;
	dst.x = 0; dst.y = 0; dst.w = 100; dst.h = 100;

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			
			dst.x = 100 * x; dst.y = 100 * y;
			unsigned int checker = BD_GetPiece(x,y);

			switch (checker) {
			case BD_WHITE_CHECKER: {
				SDL_RenderCopy(app.renderer, app.texture[TEXTURE_WHITE_CHECKER], &src, &dst);
				break;
			}
			case BD_BLACK_CHECKER: {
				SDL_RenderCopy(app.renderer, app.texture[TEXTURE_BLACK_CHECKER], &src, &dst);
				break;
			}
			case BD_WHITE_KING_CHECKER: {
				SDL_RenderCopy(app.renderer, app.texture[TEXTURE_WHITE_KING_CHECKER], &src, &dst);
				break;
			}
			case BD_BLACK_KING_CHECKER: {
				SDL_RenderCopy(app.renderer, app.texture[TEXTURE_BLACK_KING_CHECKER], &src, &dst);
				break;
			}
			}

		}
	}

}