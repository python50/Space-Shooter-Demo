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
        virtual void * call(std::string item, void * value_1=NULL, void * value_2=NULL);
        virtual void * get(std::string item);
        virtual void   set(std::string item, void * value);
        virtual void   update();//game_engine &engine);
        virtual ~controller();
        bool delete_this;
        SDL_Rect rect;
        std::string id_type;
    protected:
    private:
};

#endif // CONTROLLER_H
