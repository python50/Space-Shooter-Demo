#include "tile.h"

tile::tile(game_engine *geng,float xx, float yy, std::string image)
{
    gm_engine=geng;
    x=xx;
    y=yy;
    sprite=gm_engine->get_surface(image);
    rect.x=x;
    rect.y=y;
    rect.w=sprite->w;
    rect.h=sprite->h;
    id_type="tile";
    delete_this=0;
    no_collide=1;
}

void tile::update()
{
    gm_engine->blit(x,y,sprite);
}

tile::~tile()
{
    //dtor
}
