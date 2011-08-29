#ifndef SHIP_VIEW_H
#define SHIP_VIEW_H

#include <viewer.h>


class ship_view : public viewer
{
    public:
        ship_view();
        virtual void * call(std::string item, void * value_1=NULL, void * value_2=NULL);
        virtual void * get(std::string item);
        virtual void   set(std::string item, void * value);
        virtual void   draw();
        virtual ~ship_view();
    protected:
    private:
};

#endif // SHIP_VIEW_H
