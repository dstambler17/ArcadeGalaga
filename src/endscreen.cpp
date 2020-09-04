#include "headers/graphics.h"
#include "headers/endscreen.h"
#include "headers/music.h"



#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
namespace fs = std::__fs::filesystem;

EndScreen::EndScreen() {}
EndScreen::EndScreen(Graphics &graphics, bool isVictory) {
   
    fs::path pathToShow("content/backgrounds/");
    for (const auto& entry : fs::directory_iterator(pathToShow)) {
        auto file = entry.path().filename();
        std::string pathString = "content/backgrounds/" + file.u8string();
        SDL_Surface* bgSurface = graphics.loadImage(pathString);
        std::cout << file.c_str() << std::endl;
        if (!bgSurface){
            std::cout << "ERROR" << std::endl;
        } else {
            this->_backgroundTextures.push_back(SDL_CreateTextureFromSurface(graphics.getRenderer(), bgSurface));
        }
    }
    std::string title = (isVictory) ? "WINNER" : "GAME OVER";
    std::string info = "Press  \'s\' to continue or \'q\' to exit";
    this->_titleManager = TextManager(graphics, title, "content/fonts/OpenSans.ttf");
    this->_infoManager = TextManager(graphics, info, "content/fonts/OpenSans.ttf");
    this->screenMusic = Music("content/music/caveStoryBoss.ogg");
}


void EndScreen::draw(Graphics &graphics) {
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
    SDL_Rect titleRect = {250,200,300,100};
    SDL_Rect infoRect = {200, 315, 400, 50};
    _titleManager.draw(graphics, &titleRect);
    _infoManager.draw(graphics, &infoRect);
}
