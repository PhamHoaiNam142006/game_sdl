#ifndef KHAIBAO_H
#define KHAIBAO_H


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>



const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 500;
const int GROUND_HEIGHT = 400;
const int BALL_RADIUS = 20;
const int CACTUS_WIDTH = 60;
const int CACTUS_HEIGHT = 30;
const int GRAVITY = 1;
const int JUMP_FORCE = -17;

const int BALL_FRAME_WIDTH = 60;
const int BALL_FRAME_HEIGHT = 55;
const int TOTAL_ANIMATION_FRAMES = 3;

enum GameState { START, PLAYING, GAME_OVER };
extern int score;
extern int highScore;
extern GameState gameState;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;

extern SDL_Texture* ballTexture;
extern SDL_Texture* cactusTexture;
extern SDL_Rect startButton;
extern SDL_Rect restartButton;

const std::string ballImagePath = "kl-removebg-preview2.png";
const std::string cactusImagePath = "kiem2.png";


SDL_Texture* loadTexture(const std::string& path);

bool initAudio();
bool loadMusic(const std::string& path);
void playMusic();


struct Animation{
    SDL_Texture* texture;
    int frameWidth;
    int frameHeight;
    int totalFrames;
    int currentFrame;
    int animationSpeed;
    int frameCounter;

    Animation() : texture(nullptr), frameWidth(0), frameHeight(0),totalFrames(0), currentFrame(0), animationSpeed(10), frameCounter(0) {}

    void update();
    SDL_Rect getCurrentFrameRect() const;
};

struct Ball{
    int x, y;
    int velY;
    bool jumping;
    int radius;
    Animation animation;
    void jump();
    void update();
    SDL_Rect getRect() const;

    Ball() : x(100), y(GROUND_HEIGHT - BALL_FRAME_HEIGHT), velY(0), jumping(false),radius(BALL_RADIUS) {}
};

struct Cactus{
    int x, y;
    int width, height;
    bool isTop;
    int speed;
    Cactus() : x(SCREEN_WIDTH), y(GROUND_HEIGHT - CACTUS_HEIGHT),width(CACTUS_WIDTH), height(CACTUS_HEIGHT),isTop(false),speed(5)
    {
        if (rand() % 2 == 0)
        {
            isTop = true;
            y = GROUND_HEIGHT - CACTUS_HEIGHT-5;
        }
        speed++;
    }

    void update();
    SDL_Rect getRect() const;
};
void resetGame(Ball& ball, std::vector<Cactus>& cacti);
void handleStartScreenInput(SDL_Event& e);
void handleGameOverInput(SDL_Event& e, Ball& ball, std::vector<Cactus>& cacti);
void spawnCacti(std::vector<Cactus>& cacti, float speedMultiplier);
void renderText(const std::string& text, int x, int y, SDL_Color color);
void renderStartScreen();
void renderGameOverScreen();
void resetGame(Ball& ball, std::vector<Cactus>& cacti);

bool init();
bool loadMedia(Ball& ball);
bool checkCollision(const SDL_Rect& ballRect, const SDL_Rect& obstacleRect);

void close(Ball& ball);
#endif // KHAIBAO_H
