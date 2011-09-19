/**
 ** Code Copyright (C) 2011 Jason White <whitewaterssoftwareinfo@gmail.com>
 **                         White Waters Software - http://wwsoft.co.cc
 **
 ** modifying, copying and distribution of this source is prohibited without
 ** explicit authorization by the copyright holder: Jason White
 **/

#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//using namespace std;

error::error(error_level level,std::string message)
{

    if (level==FATAL_ERROR or level==F_ERR)
    {
        message="FATAL ERROR: "+message;
        log(message);
    }

    if (level==WARNING or level==WARN)
    {
        message="WARNING: "+message;
        log(message);
    }

    if (level==INFO_HIGH or level==INFO_H)
    {
        message="INFO HIGH: "+message;
        log(message);
    }

    if (level==INFO_MEDIUM or level==INFO_M)
    {
        message="INFO MEDIUM: "+message;
        log(message);
    }

    if (level==INFO_LOW or level==INFO_L)
    {
        message="INFO LOW: "+message;
        log(message);
    }
}


/*
*/
void error::log(std::string message)
{
    // Format Time String

    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    strftime (buffer,80,"%H:%M:%S",timeinfo);

    std::string time=buffer;

    // [12:30:02] FATAL_ERROR: Resource Not Found
    message="["+time+"] "+message+"\n";

    // Write to log

    FILE *log;
    log=fopen("error.log", "a");
    fprintf(log, message.c_str());
    printf(message.c_str());
    fclose(log);
}

error::~error()
{
    //dtor
}
