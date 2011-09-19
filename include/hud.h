#ifndef HUD_H
#define HUD_H

#include "game_engine.h"
#include <controller.h>


class hud : public controller
{
    public:
        hud(game_engine * g_engine);
        void update();
        void init();
        void reset();//game_engine &engine);
        virtual ~hud();
    protected:
    private:
        game_engine * gm_engine;
        SDL_Surface * right_hud;
        int counter;
};

#endif // HUD_H
