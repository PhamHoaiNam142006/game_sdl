#include "khaibao.h"

int score = 0;
int highScore = 0;
GameState gameState = START;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;

SDL_Texture* ballTexture = nullptr;
SDL_Texture* cactusTexture = nullptr;

SDL_Rect startButton = {300, 200, 200, 80};
SDL_Rect restartButton = {300, 250, 200, 80};


int main(int argc, char* args[])
{
    srand(time(nullptr));
    Ball ball;
    if (!initAudio()) return -1;
    if (!loadMusic("music.mp3")) return -1;
    playMusic();

    if (!init())
    {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }

    if (!loadMedia(ball))
    {
        std::cerr << "Failed to load media!" << std::endl;
        return -1;
    }

    std::vector<Cactus> cacti;
    int cactusSpawnTimer = 0;
    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            switch (gameState)
            {
            case START:
                handleStartScreenInput(e);
                break;
            case PLAYING:
                if (e.type == SDL_KEYDOWN &&
                        (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP))
                {
                    ball.jump();
                }
                break;
            case GAME_OVER:
                handleGameOverInput(e, ball, cacti);
                break;
            default:
                break;
            }
        }

        switch (gameState)
        {
        case START:
            // Start screen logic (if any)
            break;
        case PLAYING:
        {
            ball.update();

            cactusSpawnTimer++;
            if (cactusSpawnTimer >= 50 + rand() % 100)
            {
                spawnCacti(cacti,2.0f);
                cactusSpawnTimer = 0;
            }

            for (auto it = cacti.begin(); it != cacti.end(); )
            {
                it->update();

                if (it->x + it->width < 0)
                {
                    it = cacti.erase(it);
                    score++;
                    if (score > highScore)
                    {
                        highScore = score;
                    }
                }
                else
                {
                    if (checkCollision(ball.getRect(), it->getRect()))
                    {
                        gameState = GAME_OVER;
                        break;
                    }
                    ++it;
                }
            }
            break;
        }
        case GAME_OVER:
            // Game over screen logic (if any)
            break;
        default:
            break;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        switch (gameState)
        {
        case START:
            renderStartScreen();
            break;
        case PLAYING:
        {
            SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
            SDL_RenderFillRect(renderer, nullptr);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_Rect ground = {0, GROUND_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - GROUND_HEIGHT};
            SDL_RenderFillRect(renderer, &ground);

            SDL_Rect ballRect = ball.getRect();
            SDL_Rect currentFrame = ball.animation.getCurrentFrameRect();
            SDL_RenderCopy(renderer, ball.animation.texture, &currentFrame, &ballRect);

            for (const auto& cactus : cacti)
            {
                SDL_Rect cactusRect = cactus.getRect();
                SDL_RenderCopy(renderer, cactusTexture, nullptr, &cactusRect);
            }

            SDL_Color black = {0, 0, 0, 255};
            renderText("Score: " + std::to_string(score), 650, 30, black);
            break;
        }
        case GAME_OVER:
            renderGameOverScreen();
            break;
        default:
            break;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    close(ball);
    return 0;
}
