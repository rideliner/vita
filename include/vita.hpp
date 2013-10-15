/*!
 * Copyright (c) 2013
 * Nathan Currier
 *
 * Use, modification, and distribution are all subject to the
 * Boost Software License, Version 1.0. (See the accompanying
 * file LICENSE.md or at http://rideliner.tk/LICENSE.html).
 *
 * Add a wrapper to a program's entry point.
**/

#ifndef _VITA_HPP
#define _VITA_HPP

#ifndef VITA_ENTRY_POINT
# if (defined __WIN32__ || defined _WIN32) && (defined UNICODE || defined _UNICODE)
#  define VITA_ENTRY_POINT wmain // Only used in Windows
# else
#  define VITA_ENTRY_POINT main
# endif // Windows & Unicode
#endif // VITA_ENTRY_POINT

#include "vita/ortus.hpp"
#include "vita/orcus.hpp"

#define main(...) \
    VitaMain(Ortus&, Orcus&); \
    int VITA_ENTRY_POINT(int argc, Ortus::ArgvType argv, Ortus::EnvType env) \
    { return VitaMain(Ortus::initialize(argc, argv, env), Orcus::initialize()); } \
    int VitaMain(Ortus& ortus, Orcus& orcus)

#endif // _VITA_HPP

