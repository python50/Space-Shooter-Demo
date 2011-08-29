/**
 ** Code Copyright (C) 2011 Jason White <whitewaterssoftwareinfo@gmail.com>
 **                         White Waters Software - wwsoft.co.cc
 **
 ** Copying and distributing this source is prohibited without
 ** explicit authorization by the copyright holder: Jason White
 **/

#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>
#include <iostream>

/* Error.h
 *
 * Error Reporting class responsable for loging handling
 * various errors
 *
 * Error Levels:
 *
 * 1 - Error - Fatal Errors
 * 2 - Warning - Recoverable Errors
 * 3 - Info - High Level Info
 * 4 - Info - Medium Level Info
 * 5 - Info - Low Level Info
 *
 */

enum error_level
{
    FATAL_ERROR=1,
    F_ERR=1,
    WARNING=2,
    WARN=2,
    INFO_HIGH=3,
    INFO_H=3,
    INFO_MEDIUM=4,
    INFO_M=4,
    INFO_LOW=5,
    INFO_L=5
};


class error
{
    public:
        error(error_level,std::string message);
        virtual ~error();
    protected:
    private:
        void log(std::string message);
};

#endif // ERROR_H
