/**
 ** Code Copyright (C) 2011 Jason White <whitewaterssoftwareinfo@gmail.com>
 **                         White Waters Software - http://wwsoft.co.cc
 **
 ** modifying, copying and distribution of this source is prohibited without
 ** explicit authorization by the copyright holder: Jason White
 **/

#include "controller.h"

controller::controller()
{
    //ctor
}

void controller::call(std::string item, void * value_1, void * value_2)
{

}

void controller::get(std::string item, void * val)
{
    return;
}

void controller::get(std::string item, int * val)
{
    return;
}

void controller::get(std::string item, float &val)
{
    return;
}


void controller::set(std::string item, void * value)
{

}

void controller::update()
{

}

void controller::init()
{

}

void controller::reset()
{

}

controller::~controller()
{
    //dtor
}
