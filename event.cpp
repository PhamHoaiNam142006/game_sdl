#include "khaibao.h"

void handleStartScreenInput(SDL_Event& e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (mouseX >= startButton.x && mouseX <= startButton.x + startButton.w &&
                mouseY >= startButton.y && mouseY <= startButton.y + startButton.h)
        {
            gameState = PLAYING;
            score = 0; // Reset score khi bắt đầu game mới
        }
    }
    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
    {
        gameState = PLAYING;
        score = 0; // Reset score khi bắt đầu game mới
    }
}
void handleGameOverInput(SDL_Event& e, Ball& ball, std::vector<Cactus>& cacti)
{
    static bool keyProcessed = false;

    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
    {
        int mouseX = e.button.x;
        int mouseY = e.button.y;

        if (mouseX >= restartButton.x && mouseX <= restartButton.x + restartButton.w &&
                mouseY >= restartButton.y && mouseY <= restartButton.y + restartButton.h)
        {
            resetGame(ball, cacti);
            keyProcessed = false;
        }
    }
    else if (e.type == SDL_KEYDOWN && !keyProcessed)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_SPACE:
        case SDLK_RETURN:
        case SDLK_r:
            resetGame(ball, cacti);
            keyProcessed = true;
            break;

        case SDLK_ESCAPE:
            gameState = START;
            score = 0;
            cacti.clear();
            keyProcessed = true;
            break;

        default:
            break;
        }
    }
    else if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_SPACE:
        case SDLK_RETURN:
        case SDLK_r:
        case SDLK_ESCAPE:
            keyProcessed = false;
            break;
        }
    }
}
