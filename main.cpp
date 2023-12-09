#include <iostream>
#include "Config.h"
#include "libs/cxxopts/include/cxxopts.hpp"
#include <plog/Log.h>
#include <plog/Init.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/ColorConsoleAppender.h>

void setDebugLevel(std::string &level)
{
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    if (level == "DEBUG")
    {
        plog::init(plog::debug, &consoleAppender);
    }
    else if (level == "ERROR")
    {
        plog::init(plog::error, &consoleAppender);
    }
    else if (level == "VERBOSE")
    {
        plog::init(plog::verbose, &consoleAppender);
    }
    else
    {
        plog::init(plog::error, &consoleAppender);
        PLOG_ERROR<<"debug level is not set, level is forced to error";        
    }
}

int main (int arc, char **argv)
{
    std::string debug_level = "NONE";
    cxxopts::Options options("Mqtt ","home automation application");
    PLOG_DEBUG<<"version minor: "<<mqtt_VERSION_MINOR;
    PLOG_DEBUG<<"version major: "<<mqtt_VERSION_MAJOR;
    options.add_options()
    ("d, level","debug level: DEBUG, ERROR, VERBOSE" , cxxopts::value<std::string>())
    ("h, help","");
    auto parsed_options = options.parse(arc,argv);
   
    if (parsed_options.count("level"))
      debug_level = parsed_options["level"].as<std::string>();
    setDebugLevel(debug_level);
     if (parsed_options.count("help"))
    {
      PLOG_DEBUG << options.help();
      exit(0);
    }
    PLOG_DEBUG<<"starting the application";
    return 0;
}