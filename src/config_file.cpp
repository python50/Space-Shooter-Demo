/**
 ** Code Copyright (C) 2011 Jason White <whitewaterssoftwareinfo@gmail.com>
 **                         White Waters Software - http://wwsoft.co.cc
 **
 ** modifying, copying and distribution of this source is prohibited without
 ** explicit authorization by the copyright holder: Jason White
 **/

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "error.h"
#include "config_file.h"

using namespace std;

/*
    TODO:
        fix multi LUA_Stare creation
*/

config_file::config_file(string name)
{
    new error(INFO_L,"New Config File: "+name);
    //should do error checking on `name`
    filename=name;
}

/*
    Ita bad Practice to create more than one LUA_State
    it sould be created one passed around function to function
    via a refrence ...
*/

int config_file::get_int(string var_name)
{
    new error(INFO_L,"Config File `"+filename+"`: getting `"+var_name+"`");

    int number=0;

    lua_State *L = lua_open();
    luaL_openlibs(L);

    if (!luaL_dofile(L,filename.c_str())) //execute config file
    {
        lua_getglobal(L,var_name.c_str());
        if (!lua_isnumber(L, -1))
        {
            new error(WARNING,filename+": `"+var_name+"` should be a number");
        }
        else
            number=(int)lua_tonumber(L, -1);
    }
    else
    {
        new error(WARNING,"cannot execute "+filename);
    }

    lua_close(L);

    return number;
}

float config_file::get_float(string var_name)
{
    float number=0;

    lua_State *L = lua_open();
    luaL_openlibs(L);

    if (!luaL_dofile(L,filename.c_str())) //execute config file
    {
        lua_getglobal(L,var_name.c_str());
        if (!lua_isnumber(L, -1))
        {
            new error(WARNING,filename+": `"+var_name+"` should be a number");
        }
        else
            number=(float)lua_tonumber(L, -1);
    }
    else
    {
        new error(WARNING,"cannot execute "+filename);
    }

    lua_close(L);

    return number;
}

string config_file::get_string(string var_name)
{
    string data_string="";

    lua_State *L = lua_open();
    luaL_openlibs(L);

    if (!luaL_dofile(L,filename.c_str())) //execute config file
    {
        lua_getglobal(L,var_name.c_str());
        if (!lua_isstring(L, -1))
        {
            new error(WARNING,filename+": `"+var_name+"` should be a string");
        }
        else
            data_string=lua_tolstring(L, -1,NULL);
    }
    else
    {
        new error(WARNING,"cannot execute "+filename);
    }

    lua_close(L);

    return data_string;
}

config_file::~config_file()
{
    //dtor
}
