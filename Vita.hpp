/*! @file Vita.hpp
 *  @brief (Life) - Give users simplified access to Ortus and Orcus.
 *  @details Add a wrapper to the programs entry point to pass in the arguments in a different way.
 *  @author Nathan Currier
 *  @copyright Boost Software License, v1.0
**/

//! @warning Vita cannot be used with WinMain or wWinMain without hazardous consequences.

#ifndef VITA_VITA_HPP
#define VITA_VITA_HPP

#ifndef VITA_ENTRY_POINT
# if (defined __WIN32__ || defined _WIN32) && (defined UNICODE || defined _UNICODE)
#  define VITA_ENTRY_POINT wmain // Only used in Windows
# else
#  define VITA_ENTRY_POINT main
# endif // Windows & Unicode
#endif // VITA_ENTRY_POINT

#include "Ortus.hpp"
#include "Orcus.hpp"

#define main(...) \
    VitaMain(const Ortus&/*, const Orcus&*/); \
    int VITA_ENTRY_POINT(int argc, Ortus::ArgvType argv, Ortus::EnvType env) \
    { return VitaMain(Ortus::initialize(argc, argv, env)/*, Orcus::getInstance()*/); } \
    int VitaMain(const Ortus& ortus/*, const Orcus& orcus*/)

#endif // VITA_VITA_HPP
