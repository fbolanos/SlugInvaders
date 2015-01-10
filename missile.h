#include <SDL/SDL.h>
#include "SDL_Deleter.h"

class Missile
{
    public:
        Missile(int x, int y);        /// Constructor, please feed Tank pos!
        int getX() { return rect.x; } /// Gets X pos
        int getY() { return rect.y; } /// Gets Y pos
        SDL_Rect* getRect() { return &rect; } /// Returns memory address of the rect object to be drawn
        SDL_Surface* getSprite() { return sprite.get(); }
        void move();


    private:
        static const int SPEED = 4;
        SDL_Rect rect;
        UniqueSDLSurface sprite;


};
