#include <string>
#include <vector>
#include <unordered_map>

#include <iostream>

#ifndef ORTUS_CHARACTER_TYPE
# define ORTUS_CHARACTER_TYPE char
#endif // ORTUS_CHARACTER_TYPE

#ifndef ORTUS_STRING_TYPE
# define ORTUS_STRING_TYPE std::string
#endif // ORTUS_STRING_TYPE

#ifndef ORTUS_ENTRY_POINT
# define ORTUS_ENTRY_POINT main
#endif // ORTUS_ENTRY_POINT

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

    Ortus(const Ortus &from) { }
    Ortus &operator = (const Ortus &from)
    {
        return *this;
    }

    void reset()
    {
        args.clear();
        env.clear();
    }

    void addEnvironmentVariable(StrType env_var)
    {
        std::size_t marker = env_var.find_first_of('=');

        env.insert(std::make_pair<StrType, StrType>(env_var.substr(0, marker), env_var.substr(marker + 1)));
    }
  public:
    static Ortus &getInstance()
    {
        static Ortus instance;

        return instance;
    }

    static void initialize(int argc = 0, ArgvType argv = nullptr, EnvType env = nullptr)
    {
        if (argc == 0 || argv == nullptr)
            return;

        Ortus& ortus = getInstance();

        ortus.reset();

        for (int i = 0; i < argc; ++i)
            ortus.args.push_back(static_cast<StrType>(argv[i]));

        if (env == nullptr)
            return;

        while (*env != nullptr)
            ortus.addEnvironmentVariable(static_cast<StrType>(*(env++)));
    }

    const ArgsType &getArguments() const
    {
        return args;
    }

    const EnvMapType &getEnvironmentVariables() const
    {
        return env;
    }
};

#define main(...) \
  OrtusMain(const Ortus &); \
  int ORTUS_ENTRY_POINT(int argc, typename Ortus::ArgvType argv, typename Ortus::EnvType env) \
  { \
      Ortus::initialize(argc, argv, env); \
      return static_cast<int>(OrtusMain(Ortus::getInstance())); \
  } \
  int OrtusMain(const Ortus &ortus)

int main(const Ortus& ortus)
{
	for (const std::string& s : ortus.getArguments())
	    std::cout << s << std::endl;

	std::cout << std::endl;

	for (auto& x : ortus.getEnvironmentVariables())
	    std::cout << x.first << " => " << x.second << std::endl;

	return 0;
}
