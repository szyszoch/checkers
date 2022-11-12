#include "app.h"

int main(int argc, char* args[]) {

	if (App_Init() < 0) {
		App_Destroy();
		return -1;
	}

	bool IS_APP_RUNNING = true;

	while (IS_APP_RUNNING) {

		switch (AppState) {
		case APP_STATE_QUIT: {
			IS_APP_RUNNING = false;
			break;
		}
		case APP_STATE_MENU: {
			App_Menu();
			break;
		}
		case APP_STATE_GAME: {
			App_Game();
			break;
		}
		case APP_STATE_GAMEOVER: {
			App_GameOver();
			break;
		}
		default: {
			printf("Invalid state. Exiting program.\n");
			IS_APP_RUNNING = false;
			break;
		}
		}

	}

	App_Destroy();

	return 0;
}