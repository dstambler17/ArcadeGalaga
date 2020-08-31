#include "headers/textmanager.h"
#include <string> 


//Bat class
TextManager::TextManager() {}

TextManager::TextManager(Graphics &graphics)
{
    SDL_Surface* scoreSurface = graphics.loadText("content/fonts/OpenSans.ttf", "Score: 0", 40);
    SDL_Surface* levelSurface = graphics.loadText("content/fonts/OpenSans.ttf", "Level: 1", 40);
    this->_scoreTex = SDL_CreateTextureFromSurface(graphics.getRenderer(), scoreSurface);
    this->_levelTex = SDL_CreateTextureFromSurface(graphics.getRenderer(), levelSurface);
    this->_score = 0;
}

void TextManager::updateScoreTex(Graphics &graphics, int score) {
    this->_score = score;
    std::string new_score = "Score: " + std::to_string(score);
	SDL_Surface* scoreSurface = graphics.loadText("content/fonts/OpenSans.ttf", new_score, 50);
    this->_scoreTex = SDL_CreateTextureFromSurface(graphics.getRenderer(), scoreSurface);
}

void TextManager::updateLevelTex(Graphics &graphics, int level) {
    std::string new_score = "Level: " + std::to_string(level);
	SDL_Surface* levelSurface = graphics.loadText("content/fonts/OpenSans.ttf", new_score, 50);
    this->_levelTex = SDL_CreateTextureFromSurface(graphics.getRenderer(), levelSurface);
}


void TextManager::draw(Graphics &graphics) {
    SDL_Rect scoreRect = {720,20,80,40};
    SDL_Rect levelRect = {720, -10, 80, 40};
    graphics.blitSurface(this->_scoreTex, NULL, &scoreRect);
    graphics.blitSurface(this->_levelTex, NULL, &levelRect);
}


