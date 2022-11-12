#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include "button.h"

#define APP_WINDOW_TITLE "Checkers"
#define APP_WINDOW_WIDTH 600
#define APP_WINDOW_HEIGHT 600

#define APP_STATE_QUIT 0
#define APP_STATE_MENU 1
#define APP_STATE_GAME 2
#define APP_STATE_GAMEOVER 3

extern int AppState;

int App_Init();
void App_Destroy();
void App_Menu();
void App_Game();
void App_GameOver();