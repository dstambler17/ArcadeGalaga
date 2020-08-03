#include "headers/sprite.h"
#include "headers/graphics.h"

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

Sprite::Sprite() {}

Sprite::Sprite(Graphics &graphics, std::string filePath, int width, int height, int x_start, int y_start){
    SDL_Surface* spriteSurface = graphics.loadImage(filePath);
    this->_spriteTex =  SDL_CreateTextureFromSurface(graphics.getRenderer(), spriteSurface);
    //SDL_FreeSurface(spriteSurface);
    this->_destRect.w = width;
    this->_destRect.h = height;
    this->_destRect.x = x_start;
    this->_destRect.y = y_start;
    this->_x = x_start;
    this->_y = y_start;
    
}

Sprite::~Sprite() {
}

void Sprite::draw(Graphics &graphics, int x_pos, int y_pos) {
    this->_destRect.x = x_pos;
    this->_destRect.y = y_pos;
	graphics.blitSurface(this->_spriteTex, NULL, &this->_destRect);
}

void Sprite::update() {}