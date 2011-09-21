extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "game_engine.h"
#include "error.h"
#include "map_parser.h"
#include "lua_object.h"

map_parser::map_parser(game_engine * gm_engine_, std::string filename_)
{
    gm_engine=gm_engine_;
    std::string map_table="map";
    filename=filename_;

    L = lua_open();
    luaL_openlibs(L);

    new error(INFO_MEDIUM,"Loading Map `"+filename+"`");

    if (!luaL_dofile(L,filename.c_str())) //execute config file
    {
        /*lua_getglobal(L,map_table.c_str());

        if (!lua_istable(L, -1))
        {
            new error(WARNING,filename+": `map` should be a table");
            return ;
        }*/

        lua_getglobal(L,"number");
        std::cout << "number is: " << lua_tonumber(L,-1) << "\n";

        lua_getglobal(L,"map");
//        lua_pushstring(L,"layers");
//        lua_gettable(L,-2);
//        lua_pushstring(L,"size");
//        lua_gettable(L,-2);

        lua_getglobal(L,"map");
        lua_pushstring(L,"version");
        lua_gettable(L,-2);

        int index=1;
        while (1)
        {
            lua_getglobal(L,"map");
            lua_pushstring(L,"layers");
            lua_gettable(L,-2);

            lua_pushnumber(L,index);
            lua_gettable(L,-2);

            if (!lua_istable(L,-1))
                break;

            parse_layer();
            index++;
        }
    }
    else
    {
        new error(WARNING,"cannot execute "+filename);
    }

}

void map_parser::parse_layer()
{
        std::string layername;

        lua_pushstring(L,"type");
        lua_gettable(L,-2);
        layername=lua_tostring(L,-1);
        lua_pop(L,1); //pop 1 elements from the stack


        int index_objects=1;
        if (layername=="objectgroup")
        {
            while (1)
            {
                lua_pushstring(L,"objects");
                lua_gettable(L,-2);
                lua_pushnumber(L,index_objects);
                lua_gettable(L,-2);

                if (!lua_istable(L,-1))
                    break;
                parse_object();

                lua_pop(L,2);

                index_objects++;
            }
        }
        else
            std::cout << "Bad layer" << "\n";
}

void map_parser::parse_object()
{
        lua_pushstring(L,"type");
        lua_gettable(L,-2);
        std::string object_type=lua_tostring(L,-1);
        lua_pop(L,1);


        //if (lua_tostring(L,-1)=="lua_object")
        //{
            std::cout << "its a new [" << object_type <<"]\n";
        //}

        if (object_type=="lua_object")
        {
            float x,y;

            lua_pushstring(L,"x");
            lua_gettable(L,-2);
            x=lua_tonumber(L,-1);

            lua_pop(L,1);

            lua_pushstring(L,"y");
            lua_gettable(L,-2);
            y=lua_tonumber(L,-1);

            lua_pop(L,1);

            std::string script_name;
            lua_pushstring(L,"properties");
            lua_gettable(L,-2);

            lua_pushstring(L,"script");
            lua_gettable(L,-2);

            if (lua_isstring(L,-1))
            {
                script_name=lua_tostring(L,-1);
            }

            resources::control.push_back(new lua_object(gm_engine,script_name, x, y));

            lua_pop(L,2);
        }

}

map_parser::~map_parser()
{
    //dtor
}
