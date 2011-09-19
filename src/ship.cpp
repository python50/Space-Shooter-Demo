/**
 ** Code Copyright (C) 2011 Jason White <whitewaterssoftwareinfo@gmail.com>
 **                         White Waters Software - http://wwsoft.co.cc
 **
 ** modifying, copying and distribution of this source is prohibited without
 ** explicit authorization by the copyright holder: Jason White
 **/

#include "ship.h"
#include "math.h"
#include "shot.h"
#include "misc.h"
#include "collision.h"
#include "SDL_rotozoom.h"
#include <iostream>

ship::ship(game_engine * g_engine,float xx, float yy)
{
    id_type="player";

    gm_engine=g_engine;
    new error(INFO_LOW,"Ship Created");
    x=xx;
    y=yy;
    z=10;
    direction=1;
    image_angle=0;
    speed=0;
    friction=0.01;
    image_offset=-11;

    shot_counter=0;

    delete_this=0;
    persistant=0;
    no_collide=0;

    start_x=x;
    start_y=y;
    start_direction=direction;

    game::lives=10;
    god=0;

    sprites.push_back(gm_engine->get_surface("ship0_0.png"));
    sprites.push_back(gm_engine->get_surface("ship0_1.png"));
    sprites.push_back(gm_engine->get_surface("ship0_2.png"));
    sprites.push_back(gm_engine->get_surface("ship0_3.png"));
    sprites.push_back(gm_engine->get_surface("ship0_4.png"));
    sprites.push_back(gm_engine->get_surface("ship0_5.png"));
    sprites.push_back(gm_engine->get_surface("ship0_6.png"));
    sprites.push_back(gm_engine->get_surface("ship0_7.png"));
    sprites.push_back(gm_engine->get_surface("ship0_8.png"));
    sprites.push_back(gm_engine->get_surface("ship0_9.png"));
    sprites.push_back(gm_engine->get_surface("ship0_10.png"));
    sprites.push_back(gm_engine->get_surface("ship0_11.png"));
    sprites.push_back(gm_engine->get_surface("ship0_12.png"));
    sprites.push_back(gm_engine->get_surface("ship0_13.png"));
    sprites.push_back(gm_engine->get_surface("ship0_14.png"));
    sprites.push_back(gm_engine->get_surface("ship0_15.png"));

    SDL_Surface * tmpsurf=sprites.at(0);

    rect.w=sprites.at(0)->w;//round((tmpsurf->w)*(view::width/view::target_width));
    rect.h=sprites.at(0)->h;//round((tmpsurf->h)*(view::height/view::target_height));
    init();
}

void ship::init()
{
    start_x=x;
    start_y=y;
    start_direction=direction;
}

void ship::reset()
{
    x=start_x;
    y=start_y;
    direction=start_direction;
}

void ship::call(std::string item, void * value_1=NULL, void * value_2=NULL)
{

}

void ship::get(std::string item, void * return_value)
{

}

void ship::set(std::string item, void * value)
{

}

void ship::update()
{
    Uint8 *keystate = SDL_GetKeyState(NULL);

    if ( keystate[SDLK_UP] )
        speed+=play_area::scale*.15;
    if ( keystate[SDLK_LEFT] )
        direction+=10;
    if ( keystate[SDLK_RIGHT] )
        direction-=10;

    if ( keystate[SDLK_F10] )
        god=1;

    if ( keystate[SDLK_F11] )
        god=0;

    if ( keystate[SDLK_r] )
    {
        reset_counter++;
        if (reset_counter > 60)
        {
            reset_counter=0;
            game::reset=1;
        }
    }

    if ( keystate[SDLK_SPACE] )
    {
        shot_counter++;
        if (shot_counter > 20 )
        {
            float tmpx,tmpy;
            tmpx=x+(cos(round((direction/22.5)*22.5)*3.14/180)*(rect.w/4));//*(rect.w/2)); // ugly, sure ! does it work, well kind of ...
            tmpy=y-(sin(round((direction/22.5)*22.5)*3.14/180)*(rect.h/4)); // it needs improvemnt
            resources::control.push_back(new shot(gm_engine, tmpx+(rect.w/2), tmpy+(rect.h/2), round(direction/22.5)*22.5 )); //direction based off of var image_number below
            //resources::control.push_back(new shot(gm_engine, x+(rect.w/2), y+(rect.h/2), round(direction/22.5)*22.5+180 )); //direction based off of var image_number below
            //resources::control.push_back(new shot(gm_engine, x+(rect.w/2), y+(rect.h/2), round(direction/22.5)*22.5+90 )); //direction based off of var image_number below
            //resources::control.push_back(new shot(gm_engine, x+(rect.w/2), y+(rect.h/2), round(direction/22.5)*22.5+270 )); //direction based off of var image_number below

            shot_counter=0;
        }
    }

    physics();

    rect.x=x;
    rect.y=y;

    controller * self=this;
    controller * ctrl = rect_collide_all(rect,this,0);

    if (!ctrl==NULL)
    {
        if (ctrl->id_type=="astroid" && !god)
        {
            game::lives-=1;
            game::reset=true;
        }

        if (game::lives < 1)
            game::over=1;
    }

    view::x=(rect.x+(rect.w/2))-(view::width/2);
    view::y=(rect.y+(rect.h/2))-(view::height/2);

    if (view::x < 0)
        view::x=0;

    if (view::y < 0)
        view::y=0;

    if (view::x+(view::target_width) > play_area::width)
        view::x=play_area::width-view::target_width;

    if (view::y+(view::target_height) > play_area::height)
        view::y=play_area::height-view::target_height;

    //std::cout << play_area::scale_height << "\n";


    int image_number=round((direction/360)*16);
    if (image_number > 15)
        image_number=0;

    SDL_Surface * surf=sprites.at(image_number);

    //SDL_Surface * rects=SDL_CreateRGBSurface(SDL_SWSURFACE,rect.w,rect.h,8,128,64,128,128);

   //gm_engine->blit((rect.x-(rect.w/2))-image_offset,(rect.y-(rect.h/2))-image_offset,surf,0);
   gm_engine->blit(rect.x,rect.y,surf,0);
   //gm_engine->blit(rect.x,rect.y,rects,0);
}

void ship::physics()
{
    if (speed > play_area::scale*3)
        speed=play_area::scale*3; //3 is the speed constant

    if (speed > 0)
        speed-=play_area::scale*friction;
    else
        speed=0;

    //wraping
    if (direction > 360)
        direction=0;
    if (direction < 0)
        direction=360;

    if (x > play_area::scale_width)
        x=0;
    if (y > play_area::scale_height)
        y=0;

    if (x < 0)
        x=play_area::scale_width;
    if (y < 0)
        y=play_area::scale_height;

    int tmp_direction=round(direction/22.5)*22.5;
    x=x+(cos(tmp_direction*3.14/180)*speed);
    y=y-(sin(tmp_direction*3.14/180)*speed);
}

ship::~ship()
{
    //dtor
}
