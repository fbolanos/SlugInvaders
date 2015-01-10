#include <SDL/SDL.h>
#include "SDL_Deleter.h"

class Alien
{
    public:
        Alien(int x, int y);
        int getX() { return rect.x; }
        int getY() { return rect.y; }
        SDL_Surface* getSprite() { return sprite.get(); }
        SDL_Rect* getRect() { return &rect; } /// Returns memory address of the rect object to be drawn
        void move();

    private:
        static const int SPEED = 2;
        static const int JIGGLE = 1;
        int x;
        int y;
        UniqueSDLSurface sprite;
        SDL_Rect     rect;


};




