#ifndef TitleScreen_h
#define TitleScreen_h
#include "graphics.h"
#include "textmanager.h"
#include "music.h"

#include <string>
#include <iostream>
#include <vector>
using std::vector;


class TitleScreen {
    public:
        TitleScreen();
        TitleScreen(Graphics &graphics);

        /*void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        */
        void handleEvents();
        void draw(Graphics &graphics);
        Music backgroundMusic();


    private:
        vector<SDL_Texture*> _backgroundTextures;
        SDL_Texture* _titleTex;
        TextManager _aboutManager;
        TextManager _infoManager;

};

#endif