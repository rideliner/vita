/*! @file Orcus.hpp
 *  @brief (Death) - Still deciding what Orcus will do.
 *  @details
 *  @author Nathan Currier
 *  @copyright Boost Software License, v1.0
**/

#ifndef VITA_ORCUS_HPP
#define VITA_ORCUS_HPP

class Orcus
{
    // Singleton class shouldn't be copyable/constructable outside of getInstance()
    Orcus() { }
    virtual ~Orcus() { }

    Orcus(const Orcus& from) { }
    Orcus& operator = (const Orcus& from)
    {
        return *this;
    }
  public:
    static Orcus& getInstance()
    {
        static Orcus instance;

        return instance;
    }
};

#endif // VITA_ORCUS_HPP
