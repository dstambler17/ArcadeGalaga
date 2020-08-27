#include "headers/audio.h"
#include <string>
#include <iostream>


Audio::~Audio() {
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
}

void Audio::load(const char* filename) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cout << "init error" <<std::endl;
    }
    std::cout << "LOAD GOOD" <<std::endl;
    SDL_LoadWAV(filename, &wavSpec, &wavBuffer, &wavLength);
    deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}

void Audio::play() {
    std::cout << "PLAY TEST" <<std::endl;
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
}