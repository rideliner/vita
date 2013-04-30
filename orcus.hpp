/*! @file Orcus.hpp
 *  @brief (Death) - Still deciding what Orcus will do.
 *  @details
 *  @author Nathan Currier
 *  @copyright Boost Software License, v1.0
**/

#ifndef VITA_ORCUS_HPP
#define VITA_ORCUS_HPP

#include <thread>
#include <functional>
#include <cstdlib>

#if 1 // POSIX
#include <unistd.h>
#else // Windows
#endif

class Orcus
{
    bool self_destructing;

    // Singleton class shouldn't be copyable/constructable outside of getInstance()
    Orcus()
      : self_destructing(false)
    {
    }

    virtual ~Orcus() { }

    Orcus(const Orcus& from) { }
    Orcus& operator = (const Orcus& from)
    {
        return *this;
    }

    template <class D_>
    void doWork(const D_& delay, std::function<void (Orcus*)> func)
    {
        std::this_thread::sleep_for(delay);

        func(this);
    }

    template <class D_>
    void doLater(const D_& delay, std::function<void (Orcus*)> func)
    {
        std::thread(std::bind(&Orcus::doWork<D_>, std::ref(*this), std::cref(delay), func)).detach();
    }

    static Orcus& initialize()
    {
        return getInstance();
    }
  public:
    static Orcus& getInstance()
    {
        static Orcus instance;

        return instance;
    }

    template <class D_>
    void selfDestructLater(const D_& delay, int err = EXIT_FAILURE)
    {
        doLater(delay, std::bind(&Orcus::selfDestructNow, std::placeholders::_1, err));
    }

    void selfDestructNow(int err = EXIT_FAILURE)
    {
        selfDestructOnExit();

        exitNow(err);
    }

    void selfDestructOnExit()
    {
#if 1 // POSIX
        unlink(Ortus::getInstance().getArguments()[0].c_str());
#else // WINDOWS
#endif

        self_destructing = true;
    }

    template <class D_>
    void selfDestructLaterOrOnExit(const D_& delay, int err = EXIT_FAILURE)
    {
        selfDestructOnExit();

        exitLater(delay, err);
    }

    template <class D_>
    void exitLater(const D_& delay, int err = EXIT_FAILURE)
    {
        doLater(delay, std::bind(&Orcus::exitNow, std::placeholders::_1, err));
    }

    void exitNow(int err = EXIT_FAILURE)
    {
        std::exit(err);
    }

    template <class D_>
    void quickExitLater(const D_& delay, int err = EXIT_FAILURE)
    {
        doLater(delay, std::bind(&Orcus::quickExitNow, std::placeholders::_1, err));
    }

    void quickExitNow(int err = EXIT_FAILURE)
    {
        quick_exit(err);
    }

    template <class D_>
    void abortLater(const D_& delay)
    {
        doLater(delay, &Orcus::abortNow);
    }

    void abortNow()
    {
        abort();
    }

    /*
    void handleOnAbort(); ??
    void handleOnSelfDestruct();
    void handleOnExit();
    void handleOnQuickExit();
    */

    friend int VITA_ENTRY_POINT(int, Ortus::ArgvType, Ortus::EnvType);
};

#endif // VITA_ORCUS_HPP
