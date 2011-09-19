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
#include "game_engine.h"

using namespace std;

config_file::config_file(string name)
{
    new error(INFO_L,"New Config File: "+name);
    //should do error checking on `name`
    filename=name;
}

int config_file::get_int(string var_name)
{
    new error(INFO_L,"Config File `"+filename+"`: getting `"+var_name+"`");

    int number=0;

    if (!luaL_dofile(global_lua::lua,filename.c_str())) //execute config file
    {
        lua_getglobal(global_lua::lua,var_name.c_str());
        if (!lua_isnumber(global_lua::lua, -1))
        {
            new error(WARNING,filename+": `"+var_name+"` should be a number");
        }
        else
            number=(int)lua_tonumber(global_lua::lua, -1);
    }
    else
    {
        new error(WARNING,"cannot execute "+filename);
    }

    return number;
}

float config_file::get_float(string var_name)
{
    float number=0;

    if (!luaL_dofile(global_lua::lua,filename.c_str())) //execute config file
    {
        lua_getglobal(global_lua::lua,var_name.c_str());
        if (!lua_isnumber(global_lua::lua, -1))
        {
            new error(WARNING,filename+": `"+var_name+"` should be a number");
        }
        else
            number=(float)lua_tonumber(global_lua::lua, -1);
    }
    else
    {
        new error(WARNING,"cannot execute "+filename);
    }

    return number;
}

string config_file::get_string(string var_name)
{
    string data_string="";

    if (!luaL_dofile(global_lua::lua,filename.c_str())) //execute config file
    {
        lua_getglobal(global_lua::lua,var_name.c_str());
        if (!lua_isstring(global_lua::lua, -1))
        {
            new error(WARNING,filename+": `"+var_name+"` should be a string");
        }
        else
            data_string=lua_tolstring(global_lua::lua, -1,NULL);
    }
    else
    {
        new error(WARNING,"cannot execute "+filename);
    }

    return data_string;
}

config_file::~config_file()
{
    //dtor
}
