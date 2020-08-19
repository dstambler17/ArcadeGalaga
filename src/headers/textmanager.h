#ifndef TextManager_h
#define TextManager_h
#include "graphics.h"

class Graphics;

class TextManager {
    public:
        TextManager();
        TextManager(Graphics &graphics);

        void updateScoreTex(Graphics &graphics, int score);
        void draw(Graphics &graphics);
        
        int getScore() { return this->_score; }


    private:
        int _score;
        SDL_Texture* _scoreTex;
        SDL_Texture* _levelTex;
};

#endif