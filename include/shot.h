/**
 ** Code Copyright (C) 2011 Jason White <whitewaterssoftwareinfo@gmail.com>
 **                         White Waters Software - wwsoft.co.cc
 **
 ** Copying and distributing this source is prohibited without
 ** explicit authorization by the copyright holder: Jason White
 **/

#ifndef SHOT_H
#define SHOT_H

#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_net.h"

#include "game_engine.h"
#include "error.h"

#include <SDL.h>

class shot : public controller
{
    public:
        shot(game_engine * gm_engine,float xx,float yy,float dir);
        virtual void init();
        virtual void reset();
        virtual void call(std::string item, void * value_1, void * value_2);
        virtual void get(std::string item, void * return_value);
        virtual void set(std::string item, void * value);
        void update();
        void physics();
        ~shot();
    protected:
    private:
        float x;
        float y;
        float direction;
        float speed;
        SDL_Surface * sprite;
        game_engine * gm_engine;

        int life_counter; //time delay removal
};

#endif // SHOT_H
