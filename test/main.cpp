/*!
 * Copyright (c) 2013
 * Nathan Currier
 *
 * Use, modification, and distribution are all subject to the
 * Boost Software License, Version 1.0. (See the accompanying
 * file LICENSE.md or at http://rideliner.tk/LICENSE.html).
 *
 *
**/

#include <iostream>

#include <vita.hpp>

void externalCall()
{
    Ortus& ortus = Ortus::getInstance();
    Orcus& orcus = Orcus::getInstance();

    std::cout << std::endl;

    for (auto& x : ortus.getEnvironmentVariables())
        std::cout << x.first << " => " << x.second << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Test" << std::endl;
}

int main(Ortus& ortus, Orcus& orcus)
{
    orcus.exitIn(std::chrono::seconds(2), EXIT_FAILURE);
    std::this_thread::yield();
    std::this_thread::yield();

    std::cout << ortus.getArgc() << std::endl;
    for (const std::string& s : ortus.getArguments())
        std::cout << s << std::endl;

    std::cout << std::endl;

    for (int i = 0; i < ortus.getArgc(); ++i)
        std::cout << ortus.getArgv()[i] << std::endl;

    externalCall();

    return 0;
}

