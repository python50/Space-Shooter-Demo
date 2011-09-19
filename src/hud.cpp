#include "hud.h"
#include "game_math.h"
#include "misc.h"
hud::hud(game_engine * g_engine)
{
    gm_engine=g_engine;

    delete_this=0;
    persistant=0;
    no_collide=1;

    rect.w=0;
    rect.h=0;
    rect.x=0;
    rect.y=0;

    id_type="";

    right_hud=gm_engine->get_surface("hud0");
    counter=0;
    z=-10;
}

void hud::reset()
{

}

void hud::init()
{

}

void hud::update()
{
    gm_engine->blit(view::width-right_hud->w,0,right_hud,0,1);

    SDL_Surface * text= gm_engine->render_text("jura_medium-12","Ships:"+convert_int_string(game::lives));
    gm_engine->blit(gm_engine->scale_value(10),gm_engine->scale_value(10),text,0,1);

    SDL_Surface * text2= gm_engine->render_text("jura_medium-12",convert_int_string(resources::control.size()));
    gm_engine->blit(20,40,text2,0,1);

    counter++;
    if (counter > 14)
    {
        if (game::over==true)
        {
            SDL_Surface * surf= gm_engine->render_text("jura_medium-24","Game Over");
            gm_engine->blit(view::width/5,view::height/2.5,surf,0,1);
        }
    }
    if (counter > 29)
        counter=0;
}

hud::~hud()
{
    //dtor
}
