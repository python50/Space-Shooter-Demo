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
#include "collision.h"

astroid::astroid(game_engine * engine)
{
    new error(INFO_LOW,"Astroid Created");

    id_type="astroid";

    x=gmath_random(0,play_area::scale_width*10)/10;
    y=gmath_random(0,play_area::scale_height*10)/10;
    direction=gmath_random(0,3600)/10;
    image_angle=0;
    speed=play_area::scale*(1+(gmath_random(0,20)/10));
    friction=0;

    delete_this=0;
    persistant=0;
    no_collide=0;

    sprite=gm_engine->get_surface("astroid0.png");

    rect.w=sprite->w;
    rect.h=sprite->h;

    gm_engine=engine;
    z=0;
}

void astroid::init()
{

}

void astroid::reset() //simply delete at reset
{
    delete_this=1;
}

void astroid::call(std::string item, void * value_1, void * return_value)
{

}

void astroid::get(std::string item, float  &return_value)
{
    if (item=="direction")
    {
        return_value=direction;
        return;
    }
}

void astroid::set(std::string item, void * value)
{

}

void astroid::update()
{
    rect.x=x-(rect.w/2);
    rect.y=y-(rect.h/2);

    void * self=this;
    controller * ctrl = rect_collide_all(rect,this,0);
    if (!ctrl==NULL)
    {
        if (ctrl->id_type=="astroid")
        {
            float pdir;
            ctrl->get("direction",pdir);
            if (pdir >= 180 && direction )
                direction-=180;

            if (direction < 0)
                direction=360+direction;
        }


    }

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

    if (x > play_area::scale_width)//engine.get_map_width())
        x=0;
    if (y > play_area::scale_height)//engine.get_map_height())
        y=0;

    if (x < 0)
        x=play_area::scale_width;//engine.get_map_width();
    if (y < 0)
        y=play_area::scale_height;//.get_map_height();

    x=x+(cos((float) direction*3.14/180)*speed);
    y=y-(sin((float) direction*3.14/180)*speed);
}

astroid::~astroid()
{
    gm_engine->play_sound("thud_0",0);
}
