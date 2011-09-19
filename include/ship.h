/**
 ** Code Copyright (C) 2011 Jason White <whitewaterssoftwareinfo@gmail.com>
 **                         White Waters Software - wwsoft.co.cc
 **
 ** Copying and distributing this source is prohibited without
 ** explicit authorization by the copyright holder: Jason White
 **/

#ifndef SHIP_H
#define SHIP_H

#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_net.h"

#include "game_engine.h"
#include "error.h"

#include <vector>
#include <SDL.h>

class ship : public controller
{
    public:
        ship(game_engine * gm_engine,float x, float y);
        void init();
        void reset();
        virtual void call(std::string item, void * value_1, void * value_2);
        virtual void get(std::string item, void * return_value);
        virtual void set(std::string item, void * value);
        void update();
        void physics();
        virtual ~ship();
    protected:
    private:
        float x;
        float y;
        float direction;
        float image_angle;
        float speed;
        float friction;
        float image_offset;
        float start_x;
        float start_y;
        float start_direction;
        std::vector<SDL_Surface *> sprites;
        game_engine * gm_engine;
        int shot_counter;
        int reset_counter;
        bool god;
};

#endif // SHIP_H
