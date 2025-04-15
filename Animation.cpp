#include "khaibao.h"

void Animation::update()
{
    frameCounter++;
    if (frameCounter >= animationSpeed)
    {
        frameCounter = 0;
        currentFrame = (currentFrame + 1) % totalFrames;
    }
}

SDL_Rect Animation:: getCurrentFrameRect() const
{
    return {currentFrame * frameWidth, 0, frameWidth, frameHeight};
}

