#ifndef EndScreen_h
#define EndScreen_h
#include "graphics.h"
#include "textmanager.h"
#include "music.h"

#include <string>
#include <iostream>
#include <vector>
using std::vector;


class EndScreen {
    public:
        EndScreen();
        EndScreen(Graphics &graphics, bool isVictory);

        /*void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        */
        void handleEvents();
        void draw(Graphics &graphics);
        Music screenMusic;


    private:
        int number;
        int enemiesPerScreen;
        bool clear;
        vector<SDL_Texture*> _backgroundTextures;
        TextManager _titleManager;
        TextManager _scoreResManager;
        TextManager _infoManager;

};

#endif