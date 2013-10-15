/*!
 * Copyright (c) 2013
 * Nathan Currier
 *
 * Use, modification, and distribution are all subject to the
 * Boost Software License, Version 1.0. (See the accompanying
 * file LICENSE.md or at http://rideliner.tk/LICENSE.html).
 *
 * <description>
 *
 * TODO:
 * - Finish Implementing...
**/

#ifndef VITA_ORCUS_HPP
#define VITA_ORCUS_HPP

#include <thread>
#include <chrono>
#include <functional>
#include <cstdlib>

class Orcus
{
    Orcus() = default;
    virtual ~Orcus() { }

    Orcus(const Orcus&) = delete;
    Orcus& operator = (const Orcus&) = delete;

    template <class Rep_, class Period_>
    void doWorkInImpl(const std::chrono::duration<Rep_, Period_>& delay, std::function<void (Orcus*)> func)
    {
        std::this_thread::sleep_for(delay);

        std::cout << "Exiting" << std::endl;

        func(this);
    }

    template <class Clock_, class Duration_>
    void doWorkAtImpl(const std::chrono::time_point<Clock_, Duration_>& time, std::function<void (Orcus*)> func)
    {
        std::this_thread::sleep_until(time);

        func(this);
    }

    template <class Rep_, class Period_>
    void doWorkIn(const std::chrono::duration<Rep_, Period_>& delay, std::function<void (Orcus*)> func)
    {
        std::thread(std::bind(&Orcus::doWorkInImpl<Rep_, Period_>, std::ref(*this), std::cref(delay), func)).detach();
    }

    template <class Clock_, class Duration_>
    void doWorkAt(const std::chrono::time_point<Clock_, Duration_>& time, std::function<void (Orcus*)> func)
    {
        std::thread(std::bind(&Orcus::doWorkAtImpl<Clock_, Duration_>, std::ref(*this), std::cref(time), func)).detach();
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

    template <class Rep_, class Period_>
    void exitIn(const std::chrono::duration<Rep_, Period_>& delay, int err = EXIT_FAILURE)
    {
        doWorkIn(delay, std::bind(&Orcus::exitNow, std::placeholders::_1, err));
    }

    template <class Clock_, class Duration_>
    void exitAt(const std::chrono::time_point<Clock_, Duration_>& time, int err = EXIT_FAILURE)
    {
        doWorkAt(time, std::bind(&Orcus::exitNow, std::placeholders::_1, err));
    }

    void exitNow(int err = EXIT_FAILURE)
    {
        std::cout << "Test Exiting" << std::endl;

        std::exit(err);
    }

    template <class Rep_, class Period_>
    void quickExitIn(const std::chrono::duration<Rep_, Period_>& delay, int err = EXIT_FAILURE)
    {
        doWorkIn(delay, std::bind(&Orcus::quickExitNow, std::placeholders::_1, err));
    }

    template <class Clock_, class Duration_>
    void quickExitAt(const std::chrono::time_point<Clock_, Duration_>& time, int err = EXIT_FAILURE)
    {
        doWorkAt(time, std::bind(&Orcus::quickExitNow, std::placeholders::_1, err));
    }

    void quickExitNow(int err = EXIT_FAILURE)
    {
        quick_exit(err);
    }

    template <class Rep_, class Period_>
    void abortIn(const std::chrono::duration<Rep_, Period_>& delay)
    {
        doWorkIn(delay, &Orcus::abortNow);
    }

    template <class Clock_, class Duration_>
    void abortAt(const std::chrono::time_point<Clock_, Duration_>& time)
    {
        doWorkAt(time, &Orcus::abortNow);
    }

    void abortNow()
    {
        abort();
    }

    friend int VITA_ENTRY_POINT(int, Ortus::ArgvType, Ortus::EnvType);
};

#endif // VITA_ORCUS_HPP

