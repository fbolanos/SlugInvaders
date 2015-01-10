#include "missile.h"


Missile::Missile(int pos_x, int pos_y)
{
    rect.x = pos_x;
    rect.y = pos_y;
    sprite = UniqueSDLSurface(SDL_LoadBMP("missile.bmp"));
}


void Missile::move()
{
    rect.y -= SPEED;
}

