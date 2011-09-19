#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include <iostream>

class map_parser
{
    public:
        map_parser(std::string filename);
        virtual ~map_parser();
    protected:
    private:
        std::string filename;
};

#endif // MAP_PARSER_H
