/*! @file test.cpp
 *  @brief A simple test program for Vita.
 *  @details Tests the use of the specialized main (Vita) and the command line parser (Ortus).
 *  @author Nathan Currier
 *  @copyright Boost Software License, v1.0
**/

#include "vita.hpp"

#include <iostream>
#include <chrono>

void function()
{
    Ortus& ortus = Ortus::getInstance();
    Orcus& orcus = Orcus::getInstance();

    for (auto& x : ortus.getEnvironmentVariables())
        std::cout << x.first << " => " << x.second << std::endl;

//    orcus.cancelSelfDestruct();
}

int main(Ortus& ortus, Orcus& orcus)
{
    orcus.selfDestructLaterOrOnExit(std::chrono::seconds(5));

    for (const std::string& s : ortus.getArguments())
        std::cout << s << std::endl;

    std::cout << std::endl;

    function();

    return 0;
}
