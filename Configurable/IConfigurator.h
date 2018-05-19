#ifndef _I_CONFIGURATOR_
#define _I_CONFIGURATOR_

#include <map>
#include <string>
#include <list>
#include <fstream>
#include <iostream>

#include <boost/lexical_cast.hpp>
#include <cxxabi.h>
#include <Language/Demangler.hpp>

namespace Citra { namespace Configurable {

class IConfigurator
{
    public:
        virtual ~IConfigurator();

	    static IConfigurator* Instance();

        template<typename T>
	    void get(const std::string& inClassName, const std::string& inConfigName, std::list<T>& ioValue)
        {
        	std::cout << "Configure " << Language::Demangler::demangle(ioValue) << " " << inClassName << "::" << inConfigName << " = ";
	        for (const std::string& aValue : getValues(inClassName, inConfigName))
	        {
	            std::cout << aValue << " ";
	            ioValue.push_back(boost::lexical_cast<T>(aValue));
	        }
	        std::cout << std::endl;
        }

        template<typename T>
	    void get(const std::string& inClassName, const std::string& inConfigName, T& ioValue)
        {
        	ioValue = boost::lexical_cast<T>(getValue(inClassName, inConfigName));
        	std::cout << "Configure Value " << Language::Demangler::demangle(ioValue) << " " << inClassName << "::" << inConfigName << " = " << ioValue << std::endl;
        }

    protected:
	    virtual std::string getValue(const std::string& inClassName, const std::string& inConfigName) = 0;
	    virtual std::list<std::string> getValues(const std::string& inClassName, const std::string& inConfigName) = 0;

	    IConfigurator();

        static IConfigurator* m_pInstance;
};

} /* namespace Configurable*/ } /* namespace Citra */

#endif /* _I_CONFIGURATOR_ */
