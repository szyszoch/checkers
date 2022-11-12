#include "app.h"

enum TEXTURES {
	TEXTURE_WHITE_CHECKER,
	TEXTURE_BLACK_CHECKER,
	TEXTURE_WHITE_KING_CHECKER,
	TEXTURE_BLACK_KING_CHECKER,
	TEXTURE_BOARD,
	TEXTURE_SELECT,
	TEXTURE_BUTTON_NEWGAME,
	TEXTURE_BUTTON_CONTINUE,
	TEXTURE_BUTTON_QUIT,
	TEXTURES_COUNT
};

enum BUTTONS {
	BUTTON_NEWGAME,
	BUTTON_CONTINUE,
	BUTTON_QUIT,
	BUTTONS_COUNT
};

typedef struct App {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	SDL_Texture* texture[TEXTURES_COUNT];
	Button* button[BUTTONS_COUNT];
	SDL_Cursor* cursor_arrow;
	SDL_Cursor* cursor_hand;
} App;

int AppState;

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
	app.texture[TEXTURE_BUTTON_NEWGAME] = IMG_LoadTexture(app.renderer, "img/button_newgame.png");
	app.texture[TEXTURE_BUTTON_CONTINUE] = IMG_LoadTexture(app.renderer, "img/button_continue.png");
	app.texture[TEXTURE_BUTTON_QUIT] = IMG_LoadTexture(app.renderer, "img/button_exitgame.png");

	for (int i = 0; i < TEXTURES_COUNT; i++) {
		if (app.texture[i] == NULL) {
			printf("%s\n", SDL_GetError());
			return -5;
		}
	}

	// Creating buttons
	app.button[BUTTON_NEWGAME] = BN_Create(app.texture[TEXTURE_BUTTON_NEWGAME]);
	app.button[BUTTON_CONTINUE] = BN_Create(app.texture[TEXTURE_BUTTON_CONTINUE]);
	app.button[BUTTON_QUIT] = BN_Create(app.texture[TEXTURE_BUTTON_QUIT]);

	for (int i = 0; i < BUTTONS_COUNT; i++) {
		BN_SetSprite(app.button[i], (SDL_Rect) { 0, 0, 300, 50 }, BUTTON_NORMAL);
		BN_SetSprite(app.button[i], (SDL_Rect) { 0, 50, 300, 50 }, BUTTON_HOVER);
		BN_SetSprite(app.button[i], (SDL_Rect) { 0, 0, 300, 50 }, BUTTON_CLICK);
	}

	BN_SetPosition(app.button[BUTTON_NEWGAME], 150, 200, 300, 50);
	BN_SetPosition(app.button[BUTTON_CONTINUE], 150, 300, 300, 50);
	BN_SetPosition(app.button[BUTTON_QUIT], 150, 400, 300, 50);

	// Creating cursors
	app.cursor_arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	app.cursor_hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

	AppState = APP_STATE_MENU;

	return 0;
}

void App_Destroy() {

	SDL_FreeCursor(app.cursor_arrow);
	SDL_FreeCursor(app.cursor_hand);

	for (int i = 0; i < BUTTONS_COUNT; i++) {
		BN_Destroy(app.button[i]);
	}

	for (int i = 0; i < TEXTURES_COUNT; i++) {
		SDL_DestroyTexture(app.texture[i]);
	}

	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);

	IMG_Quit();
	SDL_Quit();

}

void App_Menu() {

	while (AppState == APP_STATE_MENU) {

		// Frame Cap
		SDL_Delay(1000 / 60);

		// Handle events
		SDL_PollEvent(&app.event);

			// Buttons
		for (int i = 0; i < BUTTONS_COUNT; i++) {
			BN_Update(app.button[i], &app.event);
		}

		if (BN_Clicked(app.button[BUTTON_NEWGAME])) {
			AppState = APP_STATE_GAME;
			BD_New();
			BD_Load();
		}
		else if (BN_Clicked(app.button[BUTTON_CONTINUE])) {
			AppState = APP_STATE_GAME;
			BD_Load();
		}
		else if (BN_Clicked(app.button[BUTTON_QUIT])) {
			AppState = APP_STATE_QUIT;
		}

		// Render textures

			// Background
		SDL_Rect src, dst;
		src.x = 0; src.y = 0; src.w = 600; src.h = 600;
		dst.x = 0; dst.y = 0; dst.w = 600; dst.h = 600;
		SDL_RenderCopy(app.renderer, app.texture[TEXTURE_BOARD], &src, &dst);

			// Buttons
		for (int i = 0; i < BUTTONS_COUNT; i++) {
			BN_Render(app.button[i], app.renderer);
		}

		SDL_RenderPresent(app.renderer);
		
	}
}

void App_Game() {

	BD_Load();
	bool IS_STATE_RUNNING = true;

	while (IS_STATE_RUNNING) {

		SDL_RenderClear(app.renderer);
		SDL_PollEvent(&app.event);
		App_DrawBoard();
		SDL_RenderPresent(app.renderer);


	}

}

void App_GameOver() {

}

// ===================

void App_DrawBoard() {

	SDL_Rect src, dst;
	
	// Board
	src.x = 0; src.y = 0; src.w = 600; src.h = 600;
	dst.x = 0; dst.y = 0; dst.w = 600; dst.h = 600;
	SDL_RenderCopy(app.renderer, app.texture[TEXTURE_BOARD], &src, &dst);
	
	// Checkers
	src.x = 0; src.y = 0; src.w = 75; src.h = 75;
	dst.x = 0; dst.y = 0; dst.w = 75; dst.h = 75;

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			
			dst.x = 75 * x; dst.y = 75 * y;
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
