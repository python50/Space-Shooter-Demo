#ifndef LUA_OBJECT_H
#define LUA_OBJECT_H

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "game_engine.h"
#include <controller.h>
#include "error.h"
#include "iostream"

class lua_object : public controller
{
    public:
        lua_object(game_engine * gm_engine, std::string filename, float x, float y);
        void update();
        virtual ~lua_object();
    protected:
    private:
        game_engine * gm_engine;
        SDL_Surface * sprite;
        lua_State *L;
        float x,y,z;
        bool script_error;
        std::string scriptname;
};

#endif // LUA_OBJECT_H
