#include "khaibao.h"


void renderStartScreen()
{
    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
    SDL_RenderClear(renderer);

    SDL_Color black = {0, 0, 0, 255};
    SDL_Color buttonColor = {100, 200, 100, 255};

    SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
    SDL_RenderFillRect(renderer, &startButton);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &startButton);

    renderText("START", startButton.x + 70, startButton.y + 25, black);
    renderText("JUMPING BALL GAME", 250, 100, black);
    renderText("High Score: " + std::to_string(highScore), 300, 300, black);

    SDL_RenderPresent(renderer);
}

void renderText(const std::string& text, int x, int y, SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface)
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture)
        {
            SDL_Rect rect = {x, y, surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, nullptr, &rect);
            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(surface);
    }
}
void renderGameOverScreen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
    SDL_Rect overlay = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &overlay);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 50, 50, 255};
    SDL_Color buttonColor = {70, 160, 70, 255};
    SDL_Color buttonHoverColor = {90, 180, 90, 255};

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    bool isHovering = (mouseX >= restartButton.x && mouseX <= restartButton.x + restartButton.w &&
                       mouseY >= restartButton.y && mouseY <= restartButton.y + restartButton.h);

    SDL_Color shadowColor = {100, 0, 0, 255};
    renderText("GAME OVER", 302, 142, shadowColor);
    renderText("GAME OVER", 300, 140, red);
    renderText("Your Score: " + std::to_string(score), 300, 220, white);
    renderText("High Score: " + std::to_string(highScore), 300, 180, white);

    SDL_SetRenderDrawColor(renderer,
                           isHovering ? buttonHoverColor.r : buttonColor.r,
                           isHovering ? buttonHoverColor.g : buttonColor.g,
                           isHovering ? buttonHoverColor.b : buttonColor.b,
                           isHovering ? buttonHoverColor.a : buttonColor.a);
    SDL_RenderFillRect(renderer, &restartButton);

    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_RenderDrawRect(renderer, &restartButton);

    int textWidth = 0, textHeight = 0;
    TTF_SizeText(font, "RESTART", &textWidth, &textHeight);
    renderText("RESTART",
               restartButton.x + (restartButton.w - textWidth)/2,
               restartButton.y + (restartButton.h - textHeight)/2,
               white);

    renderText("Press SPACE or ENTER to restart", 200, 350, white);
    renderText("Press ESC to return to menu", 220, 380, white);

    static Uint8 alpha = 0;
    if (alpha < 255)
    {
        alpha += 5;
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 - alpha);
        SDL_RenderFillRect(renderer, &overlay);
    }

    SDL_RenderPresent(renderer);
}
