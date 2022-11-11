#include "app.h"

int App_Init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("%s\n", SDL_GetError());
		return -1;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		printf("%s\n", SDL_GetError());
		return -2;
	}
	return 0;
}

void App_Destroy() {
	IMG_Quit();
	SDL_Quit();
}