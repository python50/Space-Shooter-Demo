/**
 ** Code Copyright (C) 2011 Jason White <whitewaterssoftwareinfo@gmail.com>
 **                         White Waters Software - wwsoft.co.cc
 **
 ** Copying and distributing this source is prohibited without
 ** explicit authorization by the copyright holder: Jason White
 **/

#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include <iostream>
using namespace std;

class config_file
{
    public:
        config_file(string name);
        int get_int(string var_name);
        float get_float(string var_name);
        string get_string(string var_name);
        virtual ~config_file();
    protected:
    private:
        string filename;
};

#endif // CONFIG_FILE_H
