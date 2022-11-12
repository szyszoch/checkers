#pragma once
#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum BN_SPRITES {
	BUTTON_NORMAL,
	BUTTON_HOVER,
	BUTTON_CLICK,
	BUTTON_SPRITE_COUNT
} BN_SPRITES;

typedef struct Button Button;

Button* BN_Create(SDL_Texture* texture);
void BN_Destroy(Button* button);
void BN_SetPosition(Button* button, int x, int y, int w, int h);
void BN_Render(Button* button, SDL_Renderer* renderer);
void BN_Update(Button* button, SDL_Event* event);
void BN_SetSprite(Button* button, SDL_Rect sprite, BN_SPRITES id);
bool BN_Clicked(Button* button);
bool BN_Hover(Button* button);