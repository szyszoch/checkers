#include "app.h"

int main(int argc, char* args[]) {

	if (App_Init() < 0) {
		App_Destroy();
		return -1;
	}

	bool IS_APP_RUNNING = true;
	int AppState = APP_STATE_MENU;

	while (IS_APP_RUNNING) {

		switch (AppState) {
		case APP_STATE_QUIT: {
			IS_APP_RUNNING = false;
			break;
		}
		case APP_STATE_MENU: {
			AppState = App_Menu();
			break;
		}
		case APP_STATE_GAME: {
			AppState = App_Menu();
			break;
		}
		case APP_STATE_GAMEOVER: {
			AppState = App_Menu();
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