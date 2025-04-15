#include "khaibao.h"



void Ball::jump()
{
    if (!jumping)
    {
        velY = JUMP_FORCE;
        jumping = true;
    }
}

void Ball::update()
{
    velY += GRAVITY;
    y += velY;
    if (y >= GROUND_HEIGHT - BALL_FRAME_HEIGHT)
    {
        y = GROUND_HEIGHT - BALL_FRAME_HEIGHT;
        velY = 0;
        jumping = false;
    }
    animation.update();
}

SDL_Rect Ball::getRect() const
{
    return {x, y, BALL_FRAME_WIDTH, BALL_FRAME_HEIGHT};
}
