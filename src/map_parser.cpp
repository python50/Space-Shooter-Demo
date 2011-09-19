extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "game_engine.h"
#include "error.h"
#include "map_parser.h"

map_parser::map_parser(std::string filename_)
{
    std::string map_table="map";
    filename=filename_;

    if (!luaL_dofile(global_lua::lua,filename.c_str())) //execute config file
    {
        lua_getglobal(global_lua::lua,map_table.c_str());

        if (!lua_istable(global_lua::lua, -1))
        {
            new error(WARNING,filename+": `map` should be a table");
            return ;
        }

        lua_getfield(global_lua::lua, -1, "");
    }
    else
    {
        new error(WARNING,"cannot execute "+filename);
    }

}

map_parser::~map_parser()
{
    //dtor
}
