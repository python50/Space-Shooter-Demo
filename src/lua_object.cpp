#include "lua_object.h"

lua_object::lua_object(game_engine * gm_engine_, std::string filename ,float xx,float yy)//, float zz, float a, float b)
{
    gm_engine=gm_engine_;
    scriptname= filename;
    script_error=0;
    x=xx;
    y=yy;
    z=0;//zz;

    std::cout << xx << yy << "\n";

    delete_this=0;
    persistant=0;
    no_collide=0;
    std::string id_type=""; //FIX

    sprite=gm_engine->get_surface("ship1");
    L = lua_open();
    luaL_openlibs(L);

    if (!luaL_dofile(L,filename.c_str())) //execute config file
    {
        lua_getglobal(L,"update");
        lua_getglobal(L,"init");
        if (!lua_isfunction(L, -1))
        {
            script_error=true;
            new error(WARNING,"`init` should be a function");
        }

        if (!lua_isfunction(L, -2))
        {
            script_error=true;
            new error(WARNING,"`update` should be a function");
        }

    }
    else
    {
        script_error=true;
        new error(WARNING,"cannot execute `"+filename+"`");
    }

    if (!script_error)
    {
        lua_getglobal (L, "init");
        lua_call (L, 0, 0);
    }

    lua_pushnumber(L,xx*16);
    lua_setglobal(L, "x");
    lua_pushnumber(L,yy*16);
    lua_setglobal(L, "y");

}

void lua_object::update()
{
    if (script_error)
        return;


    lua_getglobal (L, "update");

    lua_call (L, 0, 0);

    lua_getglobal (L, "z");
    lua_getglobal (L, "y");
    lua_getglobal (L, "x");

    x=lua_tonumber(L,-1);
    y=lua_tonumber(L,-2);
    z=lua_tonumber(L,-3);

    gm_engine->blit(x,y,sprite);
}

lua_object::~lua_object()
{
    lua_close(L);
}
