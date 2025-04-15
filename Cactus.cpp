#include "khaibao.h"


void Cactus::update(){
    x-=speed;
}
SDL_Rect Cactus:: getRect()const{
    return {x, y, width, height};
}
void spawnCacti(std::vector<Cactus>& cacti, float speedMultiplier = 2.0f) {
    int numCacti = 1 + rand() % 2;
    for (int i = 0; i < numCacti; i++) {
        Cactus newCactus;
        newCactus.speed *= speedMultiplier;  // Áp dụng hệ số tốc độ
        if (i == 1) {
            newCactus.y -= 25;
        }
        cacti.push_back(newCactus);
    }
}
