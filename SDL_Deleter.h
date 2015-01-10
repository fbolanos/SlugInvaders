#include <memory>

#ifndef SURFACE_DELETER
#define SURFACE_DELETER
struct SDLSurfaceDeleter
{
    void operator()(SDL_Surface * p) const
    {
        if (p)
        {
            SDL_FreeSurface(p);
        }
    }
};

typedef std::unique_ptr<SDL_Surface, SDLSurfaceDeleter> UniqueSDLSurface;

#endif
