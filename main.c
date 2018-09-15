#include <stdbool.h>
#include <SDL2/SDL.h>
#include "image.h"

static const uint8_t width = 100, height = 100, scale = 20;

int main(int argc, char** argv) {

	image* im = create_image(100, 100, 0xFF);

	uint8_t colour = 0;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Colour-A-Dinosaur!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width * scale, height * scale, SDL_WINDOW_OPENGL);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	bool running = true;
	SDL_Event event;

	while(running) {
		// process events
		while(SDL_PollEvent(&event)) {

			switch(event.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_MOUSEWHEEL:
					colour += event.wheel.y;
					printf("Colour: %d\n", colour);
					break;
				case SDL_MOUSEBUTTONDOWN:
					{
					int x = event.button.x;
					int y = event.button.y;

					int locX = x / scale;
					int locY = y / scale;

					switch(event.button.button) {
						case SDL_BUTTON_RIGHT:
							fill_buc(im, locX, locY, colour);
							break;
						case SDL_BUTTON_LEFT:
							set_pix(im, locX, locY, colour);
							break;
						default: break;
					}
					break;
					}
				default:
					break;
			}
		}

		// clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Draw image
		for(unsigned i = 0; i < width * height; i++) {
			uint8_t x = i % width;
			uint8_t y = i / width;
			uint8_t col = im -> _data[i];
			SDL_SetRenderDrawColor(renderer, col, col, col, 255);
			SDL_Rect rect = { x * scale, y * scale, scale, scale };
			SDL_RenderFillRect(renderer, &rect);
		}

		// show
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;

}

