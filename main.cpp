#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif


#include <SDL/SDL.h>
#include <time.h>

#include "game.h"


/* CURRENT ISSUES:
 FIXED ALL :D
*/


int main ( int argc, char** argv )
{

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);



    /* START THE GAME SETUP HERE */

    Game game;


    // Timer
    int delay = 10;

    while (!game.hasQuit())
    {
        // message processing loop
        game.handleEvents();

        if (!game.isGameOver())
        {
            game.update();
        }
        else ///GAME OVER MAN! !!!
        {
            game.gameOver();
        }


        SDL_Delay(delay);
    } // end main loop



    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
