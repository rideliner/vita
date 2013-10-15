/*!
 * Copyright (c) 2013
 * Nathan Currier
 *
 * Use, modification, and distribution are all subject to the
 * Boost Software License, Version 1.0. (See the accompanying
 * file LICENSE.md or at http://rideliner.tk/LICENSE.html).
 *
 * <description>
**/

#ifndef VITA_TEST_HPP
#define VITA_TEST_HPP

#include <gtest/gtest.h>

#include "ortus.hpp"

namespace testing {

inline GTEST_API_ void InitGoogleTest(Ortus& ortus)
{
    ::testing::InitGoogleTest(&ortus.getArgc(), ortus.getArgv());
}

} // end namespace testing

#endif // VITA_TEST_HPP

