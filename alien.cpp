#include "alien.h"

Alien::Alien(int x, int y)
{
    rect.x = x; // x-pos
    rect.y = y; // y-pos
    sprite = UniqueSDLSurface(SDL_LoadBMP("alien.bmp"));

}



void Alien::move()
{

    rect.y += SPEED;
}
