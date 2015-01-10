#include "game.h"

#include <cstdlib>
#include <ctime>
#include <iostream>


Game::Game()
{
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
        printf("Unable to set 600x800 video: %s\n", SDL_GetError());

    if (TTF_Init() < 0)
        printf("Unable to load Font: %s\n", SDL_GetError());


    setUp();
}

Game::~Game()
{
    delete tank;
    SDL_FreeSurface(screen);
    TTF_CloseFont( font );
    TTF_Quit();
    SDL_Quit();
    printf("Destructor of Game called.\n");
}


void Game::setUp()
{
    done = false;
    b_gameOver = false;
    tank = new Tank(screen);
    font = TTF_OpenFont("/usr/share/fonts/truetype/lyx/cmr10.ttf", 40);
    n_missiles = 10;
    n_kills = 0;
    srand(time(NULL)); // Needed to generate the random position and invasion time!
}



void Game::handleEvents()
{
    SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)     /// You don't want to play anymore :(
                        done = true;
                    else if (event.key.keysym.sym == SDLK_LEFT)  /// Change direction to the left!
                        tank->faceLeft();
                    else if (event.key.keysym.sym == SDLK_RIGHT) /// Change direction to right!
                        tank->faceRight();

                    else if (event.key.keysym.sym == SDLK_SPACE && (n_missiles > 0)) ///Add missile cause he's shooting!
                    {
                        missiles.emplace_back((tank->getX()+tank->getRect()->w/2), tank->getY());
                        n_missiles -= 1;
                    }
                    else if (event.key.keysym.sym == SDLK_a) ///Add Alien! Debugging
                    {
                        aliens.emplace_back(generateRandomPos(), 0);
                    }
                    else if (event.key.keysym.sym == SDLK_r && b_gameOver) /// If the game is over, you can restart it ;)!
                    {
                        restartGame();
                    }
                    break;

                }

            } // end switch
        } // end of message processin
}

void Game::update()
{
    std::string kills_text = "Kills: " + std::to_string(n_kills);
    std::string missiles_text = "Missiles: " + std::to_string(n_missiles);


    drawObjects();
    drawText(kills_text.c_str(), 200, 620);
    drawText(missiles_text.c_str(), 400, 620);
    flipScreen();

    /// NO DRAWING. LOGISTICS PLEASE.
    advanceObjects();
    invasion();
    handleCollisions();
}

void Game::advanceObjects()
{
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    tank->move();

    std::vector<Missile>::iterator it;
    for (it = missiles.begin(); it != missiles.end(); ++it)
    {
        it->move();

        if (it->getY() == 0)
        {
            missiles.erase(missiles.begin());
            break;
        }

    }


    std::vector<Alien>::iterator it2;
    for (it2 = aliens.begin(); it2 != aliens.end(); ++it2)
    {
        it2->move();

        if (it2->getY() > tank->getY())
        {
            aliens.erase(aliens.begin());
            b_gameOver = true;
            break;
        }
    }



}



void Game::drawObjects()
{

    // draw Tank
    SDL_BlitSurface(tank->getSprite(), 0, screen, tank->getRect());

    std::vector<Missile>::iterator it;
    for (it = missiles.begin(); it != missiles.end(); ++it)
        SDL_BlitSurface(it->getSprite(), 0, screen, it->getRect());

    std::vector<Alien>::iterator it2;
    for (it2 = aliens.begin(); it2 != aliens.end(); ++it2)
        SDL_BlitSurface(it2->getSprite(), 0, screen, it2->getRect());

}


void Game::drawText(const char* text, int x, int y)
{

    text_surface = TTF_RenderText_Shaded(font, text, white, black);

    SDL_Rect text_rect;
    text_rect.x = x;
    text_rect.y = y;

    SDL_BlitSurface(text_surface, 0, screen, &text_rect);
    SDL_FreeSurface(text_surface);

}

void Game::handleCollisions()
{
    /// Using Iterators!
    bool collision = false;
    std::vector<Missile>::iterator it;
    for (it = missiles.begin(); it != missiles.end(); )
    {
        if (aliens.size() > 0)
        {
            std::vector<Alien>::iterator it2;
            for (it2 = aliens.begin(); it2 != aliens.end(); )
            {
                if (areSpritesColliding((it->getRect()), it2->getRect()))
                {
                    it = missiles.erase(it);
                    it2 = aliens.erase(it2);
                    collision = true;
                    break;

                }
                else
                {
                    ++it2;
                }
            }
            if (!collision)
                ++it;
            else if (collision)
            {
                n_kills += 1;
                n_missiles += 1;
                break;
            }
        }
        else
        {
            ++it;
        }
    }
}

void Game::invasion()
{
    /// My shitty algorithm to calculate next invasion! It works... but it's ugly :(
    int n_check = rand() % 250;
    if (n_check > 245)
    {
        aliens.emplace_back(generateRandomPos(), 0);
    }
}

void Game::flipScreen()
{
    SDL_Flip(screen);
}


void Game::gameOver()
{
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    drawText("Game Over Jigguro!", 200,200);
    drawText("Press 'R' to play again.", 200, 250);
    std::string score = "Total Score: " + std::to_string(n_kills);
    drawText(score.c_str(), 200, 300);
    flipScreen();

}

void Game::restartGame()
{
    n_kills = 0;
    n_missiles = 10;
    missiles.clear();
    aliens.clear();
    b_gameOver = false;

    delete tank;
    tank = new Tank(screen);
}


int Game::generateRandomPos()
{
    return rand() % (WIDTH-100);
}

bool Game::areSpritesColliding(SDL_Rect* a, SDL_Rect* b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a->x;
    rightA = a->x + a->w;
    topA = a->y;
    bottomA = a->y + a->h;

    //Calculate the sides of rect B
    leftB = b->x;
    rightB = b->x + b->w;
    topB = b->y;
    bottomB = b->y + b->h;


    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    printf("Collision!\n");
    return true;
}



