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

#ifndef VITA_ORTUS_HPP
#define VITA_ORTUS_HPP

#include <string>
#include <vector>
#include <unordered_map>

#ifndef ORTUS_CHARACTER_TYPE
# define ORTUS_CHARACTER_TYPE char
#endif // ORTUS_CHARACTER_TYPE

class Ortus
{
  public:
    typedef ORTUS_CHARACTER_TYPE CharType;
    typedef std::basic_string<CharType> StrType;

    typedef std::vector<StrType> ArgsType;
    typedef std::unordered_map<StrType, StrType> EnvMapType;

    typedef CharType** ArgvType;
    typedef CharType** EnvType;
  private:
    // TODO: look for a way to minimize the memory cost of copying argv
    ArgsType args;
    EnvMapType envs;

    // original values passed to main
    int* argc;
    ArgvType* argv;
    EnvType* env;

    // don't allow construction outside of getInstance()
    Ortus() = default;
    virtual ~Ortus() { }

    Ortus(const Ortus&) = delete;
    Ortus& operator = (const Ortus&) = delete;

    void addEnvironmentVariable(StrType env_var)
    {
        std::size_t marker = env_var.find_first_of('=');

        envs.insert(std::make_pair<StrType, StrType>(env_var.substr(0, marker), env_var.substr(marker + 1)));
    }

    static Ortus& initialize(int& argc, ArgvType& argv, EnvType& env)
    {
        Ortus& ortus = getInstance();

        ortus.argc = &argc;
        ortus.argv = &argv;
        ortus.env = &env;

        for (int i = 0; i < argc; ++i)
            ortus.args.push_back(std::move(static_cast<StrType>(argv[i])));

        while (*env != nullptr)
            ortus.addEnvironmentVariable(std::move(static_cast<StrType>(*(env++))));

        return ortus;
    }
  public:
    static Ortus& getInstance()
    {
        static Ortus instance;

        return instance;
    }

    const ArgsType& getArguments() const
    {
        return args;
    }

    int& getArgc() const
    {
        return *argc;
    }

    ArgvType& getArgv() const
    {
        return *argv;
    }

    const EnvMapType& getEnvironmentVariables() const
    {
        return envs;
    }

    EnvType& getEnv() const
    {
        return *env;
    }

    friend int VITA_ENTRY_POINT(int, ArgvType, EnvType);
};

#endif // VITA_ORTUS_HPP

