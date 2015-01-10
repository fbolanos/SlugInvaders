#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "tank.h"
#include "missile.h"
#include "alien.h"
#include <vector>


class Game
{
    public:
        Game();
        ~Game();
        void setUp();
        void update();
        void handleEvents();
        void advanceObjects();
        void drawObjects();
        void drawText(const char* text, int x, int y);
        void flipScreen();
        void handleCollisions();
        void invasion();
        void gameOver();
        void restartGame();



        int getKillCount() { return n_kills; }
        int getMissileCount() { return n_missiles; }
        int generateRandomPos();
        bool isGameOver() { return b_gameOver; }
        bool hasQuit()  { return done; }

    private:
        static const int WIDTH = 800;
        static const int HEIGHT = 700;
        bool b_gameOver;
        bool done;
        SDL_Surface* screen;
        Tank* tank;
        Missile* missile;
        Alien* alien;
        std::vector<Missile> missiles;
        std::vector<Alien> aliens;

        SDL_Color black = {0,0,0};
        SDL_Color white = {255,255,255};
        SDL_Surface *text_surface;
        TTF_Font* font;

        int n_missiles;
        int n_kills;


        bool areSpritesColliding(SDL_Rect* a, SDL_Rect* b);

};



