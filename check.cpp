#include "khaibao.h"

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Ball Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    font = TTF_OpenFont("BungeeSpice-Regular.ttf", 24);
    if (!font)
    {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

bool loadMedia(Ball& ball)
{
    SDL_Surface* loadedSurface = IMG_Load(ballImagePath.c_str());
    if (!loadedSurface)
    {
        std::cerr << "Unable to load ball sprite sheet " << ballImagePath << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    ball.animation.texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (!ball.animation.texture)
    {
        std::cerr << "Unable to create texture from ball sprite sheet! SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(loadedSurface);
        return false;
    }

    ball.animation.totalFrames = loadedSurface->w / BALL_FRAME_WIDTH;
    ball.animation.frameWidth = BALL_FRAME_WIDTH;
    ball.animation.frameHeight = BALL_FRAME_HEIGHT;
    ball.animation.animationSpeed = 5;

    SDL_FreeSurface(loadedSurface);

    cactusTexture = loadTexture(cactusImagePath);
    if (!cactusTexture)
    {
        std::cerr << "Failed to load cactus texture!" << std::endl;
        return false;
    }

    return true;
}

bool checkCollision(const SDL_Rect& ballRect, const SDL_Rect& obstacleRect)
{
    int ballCenterX = ballRect.x + ballRect.w/2;
    int ballCenterY = ballRect.y + ballRect.h/2;
    int ballRadius = ballRect.w/2;

    int closestX = std::max(obstacleRect.x, std::min(ballCenterX, obstacleRect.x + obstacleRect.w));
    int closestY = std::max(obstacleRect.y, std::min(ballCenterY, obstacleRect.y + obstacleRect.h));

    int distanceX = ballCenterX - closestX;
    int distanceY = ballCenterY - closestY;

    return (distanceX * distanceX + distanceY * distanceY) <= (ballRadius * ballRadius)-500;
}

SDL_Texture* loadTexture(const std::string& path)
{
    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (!loadedSurface)
    {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (!newTexture)
        {
            std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}
void close(Ball& ball)
{
    if (ball.animation.texture)
    {
        SDL_DestroyTexture(ball.animation.texture);
        ball.animation.texture = nullptr;
    }
    SDL_DestroyTexture(ballTexture);
    SDL_DestroyTexture(cactusTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    ballTexture = nullptr;
    cactusTexture = nullptr;
    font = nullptr;
    renderer = nullptr;
    window = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
