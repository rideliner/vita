/*! @file Ortus.hpp
 *  @brief (Sunrise) - Give better (in my opinion) access to command line arguments.
 *  @details Store command line parameters in a vector and environment variables in a map for easier access.
 *  @author Nathan Currier
 *  @copyright Boost Software License, v1.0
**/

#ifndef VITA_ORTUS_HPP
#define VITA_ORTUS_HPP

#include <string>
#include <vector>
#include <unordered_map>

#ifndef ORTUS_CHARACTER_TYPE
# define ORTUS_CHARACTER_TYPE char
#endif // ORTUS_CHARACTER_TYPE

#ifndef ORTUS_STRING_TYPE
# define ORTUS_STRING_TYPE std::string
#endif // ORTUS_STRING_TYPE

class Ortus
{
  public:
    typedef ORTUS_CHARACTER_TYPE CharType;
    typedef ORTUS_STRING_TYPE StrType;
    typedef const CharType** ArgvType;
    typedef CharType** EnvType;
    typedef std::vector<StrType> ArgsType;
    typedef std::unordered_map<StrType, StrType> EnvMapType;
  private:
    ArgsType args;
    EnvMapType env;

    // Singleton class shouldn't be copyable/constructable outside of getInstance()
    Ortus() { }
    virtual ~Ortus() { }

    Ortus(const Ortus& from) { }
    Ortus& operator = (const Ortus& from)
    {
        return *this;
    }

    void addEnvironmentVariable(StrType env_var)
    {
        std::size_t marker = env_var.find_first_of('=');

        env.insert(std::make_pair<StrType, StrType>(env_var.substr(0, marker), env_var.substr(marker + 1)));
    }

    static Ortus& initialize(int argc, ArgvType argv, EnvType env)
    {
        Ortus& ortus = getInstance();

        for (int i = 0; i < argc; ++i)
            ortus.args.push_back(static_cast<StrType>(argv[i]));

        while (*env != nullptr)
            ortus.addEnvironmentVariable(static_cast<StrType>(*(env++)));

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

    const EnvMapType& getEnvironmentVariables() const
    {
        return env;
    }
    
    friend int VITA_ENTRY_POINT(int, ArgvType, EnvType);
};

#endif // VITA_ORTUS_HPP
