/**
 ** Code Copyright (C) 2011 Jason White <whitewaterssoftwareinfo@gmail.com>
 **                         White Waters Software - wwsoft.co.cc
 **
 ** Copying and distributing this source is prohibited without
 ** expliced authorization by the copyright holder: Jason White
 **/


extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "config_file.h"
#include "error.h"
#include "misc.h"
#include "game_engine.h"
#include <stdlib.h>
#include <SDL_framerate.h>
//#include "main.h"

int main()
{
    new error(INFO_HIGH,"WWSiGE Loading");

    game_engine engine(320,240);

    if (! engine.load(320,240,0,0))
    {
        new error(FATAL_ERROR,"WWSiGE Failed To Load Necessary Resources, Quitting ...");
        return 100;
    }

    new error(INFO_HIGH,"WWSiGE Started");

    FPSmanager manager;
    SDL_initFramerate(&manager);
    SDL_setFramerate(&manager, 30);


    while (engine.update())
    {
        SDL_framerateDelay(&manager);
    }

    new error(INFO_HIGH,"WWSiGE Closed");

    return 0;
}
