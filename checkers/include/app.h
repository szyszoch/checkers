#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#define APP_WINDOW_TITLE "Checkers"
#define APP_WINDOW_WIDTH 800
#define APP_WINDOW_HEIGHT 800

#define APP_STATE_QUIT 0
#define APP_STATE_MENU 1
#define APP_STATE_GAME 2
#define APP_STATE_GAMEOVER 3

int App_Init();
void App_Destroy();
int App_Menu();
int App_Game();
int App_GameOver();