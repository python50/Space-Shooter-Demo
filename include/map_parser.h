#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include <iostream>
#include "game_engine.h"


class map_parser
{
    public:
        map_parser(game_engine * gm_engine, std::string filename);
        virtual ~map_parser();
    protected:
    private:
        void parse_layer();
        void parse_object();

        lua_State *L;
        game_engine * gm_engine;
        std::string filename;
};

#endif // MAP_PARSER_H
