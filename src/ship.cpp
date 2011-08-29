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
#include "collision.h"
#include "SDL_rotozoom.h"
#include <iostream>

ship::ship(game_engine * g_engine)
{
    id_type="player";

    gm_engine=g_engine;
    new error(INFO_LOW,"Ship Created");

    x=160;
    y=140;
    direction=1;
    image_angle=0;
    speed=0;
    friction=0.01;
    image_offset=-11;

    shot_counter=0;

    delete_this=0;

    sprites.push_back(gm_engine->get_surface("ship0_0.png"));
    sprites.push_back(gm_engine->get_surface("ship0_1.png"));
    sprites.push_back(gm_engine->get_surface("ship0_2.png"));
    sprites.push_back(gm_engine->get_surface("ship0_3.png"));
    sprites.push_back(gm_engine->get_surface("ship0_4.png"));
    sprites.push_back(gm_engine->get_surface("ship0_5.png"));
    sprites.push_back(gm_engine->get_surface("ship0_6.png"));
    sprites.push_back(gm_engine->get_surface("ship0_7.png"));
}

void * ship::call(std::string item, void * value_1=NULL, void * value_2=NULL)
{

}

void * ship::get(std::string item)
{

}

void ship::set(std::string item, void * value)
{

}

void ship::update()
{
    Uint8 *keystate = SDL_GetKeyState(NULL);

    if ( keystate[SDLK_UP] )
        speed+=.15;
    if ( keystate[SDLK_LEFT] )
        direction+=10;
    if ( keystate[SDLK_RIGHT] )
        direction-=10;

    if ( keystate[SDLK_SPACE] )
    {
        shot_counter++;
        if (shot_counter > 20)
        {
            resources::control.push_back(new shot(gm_engine, x, y, round(direction/45)*45 )); //direction based off of var image_number below
            shot_counter=0;
        }
    }

    //void * result;
    controller * self=this;

    rect.x=x;
    rect.y=y;
    rect.w=16;
    rect.h=16;
/*    SDL_Rect rect_;
    rect_.x=0;
    rect_.y=0;
    rect_.w=1;
    rect_.h=1;*/

    //controller * ctrl = rect_collide_all(rect,self,0);

    if (!rect_collide_all(rect,self,0)==NULL)
    {
        speed=0;
    }


    physics();

    int image_number=round((direction/360)*8);
    if (image_number > 7)
        image_number=0;

    SDL_Surface * surf=sprites.at(image_number);

    gm_engine->blit(x+round(image_offset),y+round(image_offset),surf,0);
}

void ship::physics()
{
    if (speed > 3)
        speed=3;
    if (speed > 0)
        speed-=friction;
    else
        speed=0;
    //wraping
    if (direction > 360)
        direction=0;
    if (direction < 0)
        direction=360;

    if (x > 640)
        x=0;
    if (y > 480)
        y=0;

    if (x < 0)
        x=640;
    if (y < 0)
        y=480;

    int tmp_direction=round(direction/45)*45;
    x=x+(cos(tmp_direction*3.14/180)*speed);
    y=y-(sin(tmp_direction*3.14/180)*speed);
}

ship::~ship()
{
    //dtor
}
