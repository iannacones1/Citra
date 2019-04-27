#ifndef _I_CONFIGURATOR_
#define _I_CONFIGURATOR_

#include <map>
#include <string>
#include <list>
#include <fstream>
#include <iostream>

#include <Language/Demangler.hpp>
#include <Language/Lexical.hpp>

namespace Citra { namespace Configurable {

class IConfigurator
{
    public:
        virtual ~IConfigurator();

	    static IConfigurator* Instance();
        static bool help();

        template<typename T>
        void get(const std::string& inClassName, const std::string& inConfigName, std::list<T>& ioValue)
        {
            if (mHelp)
            {
                help(inClassName, inConfigName, Language::Demangler::demangle(ioValue), "");
                for (const std::string& aValue : getValues(inClassName, inConfigName))
                {
                    ioValue.push_back(Language::Lexical::fromString<T>(aValue));
                }
            }
            else
            {
                std::cout << "Configure " << Language::Demangler::demangle(ioValue) << " " << inClassName << "::" << inConfigName << " = ";
                for (const std::string& aValue : getValues(inClassName, inConfigName))
                {
                    std::cout << aValue << " ";
                    ioValue.push_back(Language::Lexical::fromString<T>(aValue));
                }
                std::cout << std::endl;
            }
        }

        template<typename T>
        void get(const std::string& inClassName, const std::string& inConfigName, T& ioValue)
        {
            if (mHelp)
            {
                help(inClassName, inConfigName, Language::Demangler::demangle(ioValue), Language::Lexical::toString(ioValue));

                try
                {
                    ioValue = Language::Lexical::fromString<T>(getValue(inClassName, inConfigName));
                }
                catch(...) { }

                return;
            }
            else if (isInitialised(ioValue))
            {
                T aLocal = T();
                try
                {
                    aLocal = Language::Lexical::fromString<T>(getValue(inClassName, inConfigName));
                }
                catch(...) { }

                if (isInitialised(aLocal))
                {
                    ioValue = aLocal;
                }
            }
            else
            {
        	    ioValue = Language::Lexical::fromString<T>(getValue(inClassName, inConfigName));
            }

            std::cout << " " << inClassName << "::" << inConfigName << " [" << Language::Demangler::demangle(ioValue) << " = " << ioValue << "]" << std::endl;
        }


    protected:
        template<typename T>
        static bool isInitialised(const T& aValue)
        {
            return aValue != T();
        }

	    virtual std::string getValue(const std::string& inClassName, const std::string& inConfigName) = 0;
	    virtual std::list<std::string> getValues(const std::string& inClassName, const std::string& inConfigName) = 0;

	    virtual void help(const std::string& inClassName, const std::string& inConfigName, const std::string& inType, const std::string& inDefaultValue)
	    {
            std::cout << "HELP Configure " << inType << " " << inClassName << "::" << inConfigName;

            if (isInitialised(inDefaultValue))
            {
                std::cout << " = " << inDefaultValue;
            }

            std::cout << std::endl;
	    }

	    IConfigurator(int argc, char* argv[]);

        static IConfigurator* m_pInstance;

    private:
        bool mHelp;
};

// consider all booleans initialised, because default construction is valid
template <>
inline bool IConfigurator::isInitialised<bool>(const bool&)
{
    return true;
}

} /* namespace Configurable*/ } /* namespace Citra */

#endif /* _I_CONFIGURATOR_ */
