/**
 ** Code Copyright (C) 2011 Jason White <whitewaterssoftwareinfo@gmail.com>
 **                         White Waters Software - http://wwsoft.co.cc
 **
 ** modifying, copying and distribution of this source is prohibited without
 ** explicit authorization by the copyright holder: Jason White
 **/

#include "game_math.h"
#include "stdlib.h"
#include "time.h"

void gmath_randomize()
{
    srand ( time(NULL) );
}

int gmath_random(int low , int high)
{
    return rand() % (high-low+1) + low;
}
