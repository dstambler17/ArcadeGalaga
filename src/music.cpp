#include "headers/music.h"
#include <string>
#include <iostream>

using namespace std;

Music::Music() {}
Music::Music(std::string filePath) {
    this->musique = Mix_LoadMUS(filePath.c_str());
    if (this->musique == NULL){
        cout << "MUSIC ERR" << endl;
    }
}

void Music::play() {
    Mix_HaltMusic();
    if (!Mix_PlayingMusic()){
        if(Mix_PlayMusic(this->musique, -1)==-1) {
            cout << Mix_GetError() << endl;
        }
 
    }
}
