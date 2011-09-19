/**
 ** Code Copyright (C) 2011 Jason White <whitewaterssoftwareinfo@gmail.com>
 **                         White Waters Software - http://wwsoft.co.cc
 **
 ** modifying, copying and distribution of this source is prohibited without
 ** explicit authorization by the copyright holder: Jason White
 **/

#ifndef VIEWER_H
#define VIEWER_H
#include "iostream"

class viewer
{
    public:
        viewer();
        virtual void * call(std::string item, void * value_1=NULL, void * value_2=NULL);
        virtual void * get(std::string item);
        virtual void   set(std::string item, void * value);
        virtual void   draw();
        virtual ~viewer();
    protected:
    private:
};

#endif // VIEWER_H
