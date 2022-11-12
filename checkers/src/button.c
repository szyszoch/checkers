#include "button.h"

typedef struct Button {
	SDL_Texture* texture;
	SDL_Rect *src, dst;
	SDL_Rect sprite[BUTTON_SPRITE_COUNT];
	bool HOVER, CLICK;
} Button;

Button* BN_Create(SDL_Texture* texture) {
	
	if (texture == NULL) {
		printf("Invalid texture\n");
		return NULL;
	}

	Button* new_button = malloc(sizeof(Button));
	if (new_button == NULL) {
		printf("Can't allocate memory\n");
		return NULL;
	}

	new_button->texture = texture;
	
	int width, height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	SDL_Rect temp;

	temp.x = 0;
	temp.y = 0;
	temp.w = width;
	temp.h = height;

	new_button->dst.x = 0;
	new_button->dst.y = 0;
	new_button->dst.w = width;
	new_button->dst.h = height;

	for (int i = 0; i < BUTTON_SPRITE_COUNT; i++) {
		new_button->sprite[i] = temp;
	}

	new_button->src = &new_button->sprite[BUTTON_NORMAL];
	new_button->HOVER = false;
	new_button->CLICK = false;

	return new_button;

}

void BN_Destroy(Button* button) {
	if (button == NULL) {
		return;
	}
	free(button);
}

void BN_SetPosition(Button* button, int x, int y, int w, int h) {
	button->dst.x = x;
	button->dst.y = y;
	button->dst.w = w;
	button->dst.h = h;
}

void BN_Render(Button* button, SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, button->texture, button->src, &button->dst);
}

void BN_Update(Button* button, SDL_Event* event) {
	
	button->HOVER = false;
	button->CLICK = false;

	// Normal
	button->src = &button->sprite[BUTTON_NORMAL];

	// Hover
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	SDL_Rect mouse = { mx, my, 1, 1 };
	if (SDL_HasIntersection(&button->dst, &mouse)) {
		
		button->HOVER = true;
		button->src = &button->sprite[BUTTON_HOVER];

		// Click
		if ((event->type == SDL_MOUSEBUTTONDOWN) && (event->button.button == SDL_BUTTON_LEFT)) {
			button->src = &button->sprite[BUTTON_CLICK];
			button->CLICK = true;
		}

	}

}

void BN_SetSprite(Button* button, SDL_Rect sprite, BN_SPRITES id) {
	button->sprite[id] = sprite;
}

bool BN_Clicked(Button* button) {
	return button->CLICK;
}

bool BN_Hover(Button* button) {
	return button->HOVER;
}

