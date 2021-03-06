/**
 ** Code Copyright (C) 2011 Jason White <whitewaterssoftwareinfo@gmail.com>
 **                         White Waters Software - wwsoft.co.cc
 **
 ** Copying and distributing this source is prohibited without
 ** explicit authorization by the copyright holder: Jason White
 **/

#ifndef CONTROLLER_H
#define CONTROLLER_H

//#include "game_engine.h"
#include <iostream>
#include "SDL.h"

class controller
{
    public:
        controller();
        virtual void call(std::string item, void * value_1=NULL, void * return_value=NULL);
        virtual void get(std::string item, void * return_value=NULL);
        virtual void get(std::string item, int * return_value=NULL);
        virtual void get(std::string item, float &return_value);
        virtual void   set(std::string item, void * value);
        virtual void   update();
        virtual void init();
        virtual void reset();//game_engine &engine);
        virtual ~controller();
        bool delete_this;
        bool persistant;
        bool no_collide;
        SDL_Rect rect;
        std::string id_type;
        float z;
    protected:
    private:
};

#endif // CONTROLLER_H
