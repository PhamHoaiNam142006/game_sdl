#include "khaibao.h"

void resetGame(Ball& ball, std::vector<Cactus>& cacti)
{
    gameState = PLAYING;
    score = 0;
    cacti.clear();
    ball = Ball();

    if (ball.animation.texture)
    {
        SDL_DestroyTexture(ball.animation.texture);
        ball.animation.texture = nullptr;
    }

    SDL_Surface* loadedSurface = IMG_Load(ballImagePath.c_str());
    if (loadedSurface)
    {
        ball.animation.texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        ball.animation.frameWidth = BALL_FRAME_WIDTH;
        ball.animation.frameHeight = BALL_FRAME_HEIGHT;
        ball.animation.totalFrames = loadedSurface->w / BALL_FRAME_WIDTH;
        ball.animation.animationSpeed = 5;
        ball.animation.currentFrame = 0;
        ball.animation.frameCounter = 0;
        SDL_FreeSurface(loadedSurface);
    }
}
