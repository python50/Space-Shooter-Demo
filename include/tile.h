#ifndef TILE_H
#define TILE_H

#include "game_engine.h"
#include <controller.h>


class tile : public controller
{
    public:
        tile(game_engine * gengine,float x, float y, std::string image);
        virtual void update();
        virtual ~tile();
    protected:
    private:
        game_engine * gm_engine;
        SDL_Surface * sprite;
        float x;
        float y;
};

#endif // TILE_H
