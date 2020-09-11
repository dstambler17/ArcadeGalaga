#include "headers/graphics.h"
#include "headers/titlescreen.h"
#include "headers/music.h"

#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
namespace fs = std::__fs::filesystem;

TitleScreen::TitleScreen() {}
TitleScreen::TitleScreen(Graphics &graphics) {
   
    fs::path pathToShow("content/backgrounds/");
    for (const auto& entry : fs::directory_iterator(pathToShow)) {
        auto file = entry.path().filename();
        std::string pathString = "content/backgrounds/" + file.u8string();
        SDL_Surface* bgSurface = graphics.loadImage(pathString);
        if (!bgSurface){
            std::cout << "ERROR WITH BG SURFACE" << std::endl;
        } else {
            this->_backgroundTextures.push_back(SDL_CreateTextureFromSurface(graphics.getRenderer(), bgSurface));
        }
    }
    std::string title = "Arcade Space";
    std::string about = "A Dan Stam Production";
    std::string info = "Press  the spacebar to start";
    this->_titleManager = TextManager(graphics, title, "content/fonts/OpenSans.ttf");
    this->_aboutManager = TextManager(graphics, about, "content/fonts/OpenSans.ttf");
    this->_infoManager = TextManager(graphics, info, "content/fonts/OpenSans.ttf");
}


void TitleScreen::draw(Graphics &graphics) {
    //Draw BG First
    SDL_Rect bgTile = {0,0,100, 100};
    int tile_num = 0;
    for (int x = 0; x < 8; x++){
        bgTile.x = x * 100;
        for (int y = 0; y < 6; y++){
            bgTile.y = y * 100;
            graphics.blitSurface(this->_backgroundTextures.at(tile_num), NULL, &bgTile);
            tile_num = (tile_num + 1) % this->_backgroundTextures.size();
           
        }
    }
    SDL_Rect titleRect = {250,150,300,100};
    SDL_Rect aboutRect = {200,260,400,50};
    SDL_Rect infoRect = {200, 340, 400, 50};
    _titleManager.draw(graphics, &titleRect);
    _aboutManager.draw(graphics, &aboutRect);
    _infoManager.draw(graphics, &infoRect);
}
