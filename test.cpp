/*! @file test.cpp
 *  @brief A simple test program for Vita.
 *  @details Tests the use of the specialized main (Vita) and the command line parser (Ortus).
 *  @author Nathan Currier
 *  @copyright Boost Software License, v1.0
**/

#include "Vita.hpp"

#include <iostream>

void function()
{
    const Ortus& ortus = Ortus::getInstance();

    for (auto& x : ortus.getEnvironmentVariables())
        std::cout << x.first << " => " << x.second << std::endl;
}

int main(const Ortus& ortus, const Orcus& orcus)
{
    for (const std::string& s : ortus.getArguments())
        std::cout << s << std::endl;

    std::cout << std::endl;

    function();

    return 0;
}
