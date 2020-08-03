#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include "headers/graphics.h"
using namespace std;

/* Graphics class
 * Holds all information dealing with graphics for the game
 */

Graphics::Graphics() {
    SDL_CreateWindowAndRenderer(800, 600, 0, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "Arcade Space Galaga");
    SDL_SetRenderDrawColor(this->_renderer, 255, 255, 255, 255);
}

Graphics::~Graphics() {
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath) {
    
    if (this->_spriteSheets.count(filePath) == 0) {
        std::cout << 'TEST' << std::endl;
		this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return this->_spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle) {
    SDL_RenderCopy(this->_renderer, texture, sourceRectangle, destinationRectangle);
}


void Graphics::flip() {
    //std::cout << 'flip' << std::endl;
	SDL_RenderPresent(this->_renderer);
}

void Graphics::clear() {
    //std::cout << 'clear' << std::endl;
	SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
	return this->_renderer;
}