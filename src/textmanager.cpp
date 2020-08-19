#include "headers/textmanager.h"
#include <string> 


//Bat class
TextManager::TextManager() {}

TextManager::TextManager(Graphics &graphics)
{
    SDL_Surface* scoreSurface = graphics.loadText("content/fonts/OpenSans.ttf", "Score: 0", 40);
    this->_scoreTex = SDL_CreateTextureFromSurface(graphics.getRenderer(), scoreSurface);
    this->_score = 0;
}

void TextManager::updateScoreTex(Graphics &graphics, int score) {
    this->_score = score;
    std::string new_score = "Score: " + std::to_string(score);
	SDL_Surface* scoreSurface = graphics.loadText("content/fonts/OpenSans.ttf", new_score, 50);
    this->_scoreTex = SDL_CreateTextureFromSurface(graphics.getRenderer(), scoreSurface);
}


void TextManager::draw(Graphics &graphics) {
    SDL_Rect scoreRect = {720,-7,80,40};
    graphics.blitSurface(this->_scoreTex, NULL, &scoreRect);
}


