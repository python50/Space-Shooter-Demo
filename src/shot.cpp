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
    z=9;
    direction=dir;
    speed=play_area::scale*6;

    life_counter=0;

    delete_this=0;
    persistant=0;
    no_collide=0;

    sprite=gm_engine->get_surface("shot0.png");
    gm_engine->play_sound("beep1");

    rect.w=round(sprite->w * (view::width/view::target_width));
    rect.h=round(sprite->h * (view::height/view::target_height));
}

void shot::init()
{

}

void shot::reset()
{
    delete_this=1;
}

void shot::call(std::string item, void * value_1, void * value_2)
{

}

void shot::get(std::string item, void * return_value)
{

}

void shot::set(std::string item, void * value)
{

}

void shot::update()
{
    life_counter++;

    rect.x=x-(rect.w/2);
    rect.y=y-(rect.h/2);

    void * self=this;
    controller * ctrl = rect_collide_all(rect,this,0);
    if (!ctrl==NULL)
    {
        if (ctrl->id_type=="astroid")
        {
            ctrl->delete_this=true;
            delete_this=true;
        }
    }

    physics();
    gm_engine->blit(x,y,sprite,0);
//std::cout << rect.x << " " << rect.y << " ; " << rect.w << " " << rect.h << "\n";
    if (life_counter > 60)
        delete_this=true;
}

void shot::physics()
{

    if (x > play_area::scale_width)
       x=0;
    if (y > play_area::scale_height)
       y=0;

    if (x < 0)
        x=play_area::scale_width;
    if (y < 0)
        y=play_area::scale_height;

    x=x+(cos(direction*3.14/180)*speed);
    y=y-(sin(direction*3.14/180)*speed);
}

shot::~shot()
{
    gm_engine->play_sound("beep1_short");
}
