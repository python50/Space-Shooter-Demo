/**
 ** Code Copyright (C) 2011 Jason White <whitewaterssoftwareinfo@gmail.com>
 **                         White Waters Software - wwsoft.co.cc
 **
 ** Copying and distributing this source is prohibited without
 ** explicit authorization by the copyright holder: Jason White
 **/

#ifndef ASTROID_H
#define ASTROID_H

#include "game_engine.h"

class astroid : public controller
{
    public:
        astroid(game_engine * engine);
        void init();
        void reset();
        virtual void call(std::string item, void * value_1, void * value_2);
        virtual void get(std::string item, float &return_value);
        virtual void  set(std::string item, void * value);
        void update();
        void physics();
        virtual ~astroid();
    protected:
    private:
        float x;
        float y;
        float direction;
        float image_angle;
        float speed;
        float friction;

        SDL_Surface * sprite;

        game_engine *gm_engine;
};

#endif // ASTROID_H
