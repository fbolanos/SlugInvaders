#include "tank.h"



Tank::Tank(SDL_Surface* screen)
{
    rect.x = (screen->w)/2;
    rect.y = (screen->h)-200;
    sprite = SDL_LoadBMP("tank.bmp");

    if (!sprite)
        printf("Unable to find sprite %s\n", SDL_GetError());

    MAX_X = screen->w - sprite->w;
    direction = 1; /// Default


}

Tank::~Tank()
{
    SDL_FreeSurface(sprite);
    printf("Deleted Tank\n");
}


void Tank::faceLeft(){
    direction = -1;
}

void Tank::faceRight(){
    direction = 1;
}


int Tank::getX() { return rect.x; }

int Tank::getY() { return rect.y; }

void Tank::move()
{
    rect.x += (SPEED*direction);
    handleBounds();
}

void Tank::handleBounds()
{
    if (rect.x>=MAX_X)
        rect.x = MAX_X;
    else if(rect.x<0)
        rect.x = 0;
}
