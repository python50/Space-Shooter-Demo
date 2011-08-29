/**
 ** Code Copyright (C) 2011 Jason White <whitewaterssoftwareinfo@gmail.com>
 **                         White Waters Software - http://wwsoft.co.cc
 **
 ** modifying, copying and distribution of this source is prohibited without
 ** explicit authorization by the copyright holder: Jason White
 **/

#include "shot.h"
#include "math.h"
#include "SDL_rotozoom.h"
#include <iostream>
#include "collision.h"

shot::shot(game_engine * g_engine,float xx,float yy,float dir)
{
    id_type="shot";

    gm_engine=g_engine;
    new error(INFO_LOW,"Shot Created");

    x=xx;
    y=yy;
    direction=dir;
    speed=6;

    life_counter=0;

    delete_this=0;

    sprite=gm_engine->get_surface("shot0.png");
    gm_engine->play_sound("beep1");
}

void * shot::call(std::string item, void * value_1, void * value_2)
{

}

void * shot::get(std::string item)
{

}

void shot::set(std::string item, void * value)
{

}

void shot::update()
{
    life_counter++;
    rect.x=x;
    rect.y=y;
    rect.w=2;
    rect.h=2;

    void * self=this;
    controller * ctrl = rect_collide_all(rect,this,0);
    if (!ctrl==NULL)
    {
        if (ctrl->id_type=="astroid")
        {
            ctrl->delete_this=1;
            delete_this=true;
        }
    }

    physics();
    gm_engine->blit(x,y,sprite,0);

    if (life_counter > 60)
        delete_this=true;
}

void shot::physics()
{

    if (x > 640)
       x=0;
    if (y > 480)
       y=0;

    if (x < 0)
        x=640;
    if (y < 0)
        y=480;

    x=x+(cos(direction*3.14/180)*speed);
    y=y-(sin(direction*3.14/180)*speed);
}

shot::~shot()
{
    gm_engine->play_sound("beep1_short");
}
