#include <SDL/SDL.h>




class Tank
{
    public:
        Tank(SDL_Surface* screen); /// Constructor of class tank, takes x position!

        ~Tank();

        void faceLeft(); /// Changes Direction of Tank to right

        void faceRight(); /// Changes Direction of Tank to left

        int getX(); /// Returns the X position of tank.

        int getY(); /// Returns Y pos.

        SDL_Surface* getSprite() { return sprite; }

        SDL_Rect*    getRect() { return &rect; }

        void move(); /// Moves the tank using constant dX.

        void handleBounds(); /// Checks to make sure tank doesn't go off screen.

    private:
        static const int SPEED = 8;
        int direction; /// Facing right!
        SDL_Surface* sprite;
        SDL_Rect rect;
        int MAX_X;

};
