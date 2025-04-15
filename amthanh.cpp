#include "khaibao.h"

bool initAudio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}
Mix_Music* bgMusic = nullptr;

bool loadMusic(const std::string& path) {
    bgMusic = Mix_LoadMUS(path.c_str());
    if (!bgMusic) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void playMusic() {
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(bgMusic, -1); // -1 = lặp vô hạn
    }
}
void closeAudio() {
    Mix_FreeMusic(bgMusic);
    bgMusic = nullptr;
    Mix_CloseAudio();
}
