/**
 ** Code Copyright (C) 2011 Jason White <whitewaterssoftwareinfo@gmail.com>
 **                         White Waters Software - http://wwsoft.co.cc
 **
 ** modifying, copying and distribution of this source is prohibited without
 ** explicit authorization by the copyright holder: Jason White
 **/

#include "astroid.h"
#include "error.h"
#include "SDL_rotozoom.h"
#include "game_math.h"
#include "misc.h"

astroid::astroid(game_engine * engine)
{
    new error(INFO_LOW,"Astroid Created");

    id_type="astroid";

    x=gmath_random(0,6400)/10;
    y=gmath_random(0,4800)/10;
    direction=gmath_random(0,3600)/10;
    image_angle=0;
    speed=1+(gmath_random(0,40)/10);
    friction=0;

    delete_this=0;

    rect.w=16;
    rect.h=16;

    sprite=gm_engine->get_surface("astroid0.png");

    gm_engine=engine;
}


void * astroid::call(std::string item, void * value_1=NULL, void * value_2=NULL)
{

}

void * astroid::get(std::string item)
{

}

void astroid::set(std::string item, void * value)
{

}

void astroid::update()
{
    rect.x=x-8;
    rect.y=y-8;

    physics();
    //rotozoomSurface(gm_engine->get_surface("astroid0.png"), image_angle, 1, 0)
    //SDL_Surface * surf = SDL_CreateRGBSurface(SDL_SWSURFACE,2,2,8,255,255,255,255);
    gm_engine->blit(x-sprite->w/2,y-sprite->h/2,sprite);
    //image_angle+=1;
}

void astroid::physics()
{
    //new error(INFO_L,convert_int_string( engine.get_map_width() ));
    //wraping
    if (direction > 360)
        direction=0;
    if (direction < 0)
        direction=360;

    if (x > 640)//engine.get_map_width())
        x=0;
    if (y > 480)//engine.get_map_height())
        y=0;

    if (x < 0)
        x=639;//engine.get_map_width();
    if (y < 0)
        y=479;//.get_map_height();

    x=x+(cos((float) direction*3.14/180)*speed);
    y=y-(sin((float) direction*3.14/180)*speed);
}

astroid::~astroid()
{
    gm_engine->play_sound("thud_0",0);
}
