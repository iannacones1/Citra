#ifndef _CONFIGURATOR_
#define _CONFIGURATOR_

#include <map>
#include <string>
#include <list>
#include <fstream>

#include <boost/lexical_cast.hpp>

namespace thermostat {

struct Configuration
{
  Configuration(const std::string& inSource,
                const std::string& inName,
                const std::string& inValue)
   : Source(inSource), Name(inName), Value(inValue)
  { }

  std::string Source;
  std::string Name;
  std::string Value;
};

class Configurator
{
    public:
        virtual ~Configurator() {}

	static Configurator* Instance();
	void addFileData(const std::string& inConfigFile);

        template<typename T>
	void get(const std::string& inClassName, const std::string& inConfigName, std::list<T>& ioValue)
        {
            std::cout << "Configure List " << inClassName << "::" << inConfigName << std::endl; 
	    for (const Configuration& aConfig : mConfigurations)
	    {
	        if (aConfig.Source == inClassName && aConfig.Name == inConfigName)
                {
	            ioValue.push_back(boost::lexical_cast<T>(aConfig.Value));
	        }
	    }
        }

        template<typename T>
	void get(const std::string& inClassName, const std::string& inConfigName, T& ioValue)
        {
            std::cout << "Configure " << inClassName << "::" << inConfigName << std::endl; 
	    for (const Configuration& aConfig : mConfigurations)
	    {
	        if (aConfig.Source == inClassName && aConfig.Name == inConfigName)
                {
                    ioValue = boost::lexical_cast<T>(aConfig.Value);
	    	    return;
	        }
	    }
            std::cerr << "unknown configuration " << inClassName << "::" << inConfigName << std::endl; 
            throw;
        }

    protected:
        Configurator() { };
        Configurator(const Configurator&) {};
        Configurator& operator=(const Configurator&) { return *this; };

        static Configurator* m_pInstance;
        std::list<Configuration> mConfigurations;

};

} /* namespace thermostat */

#endif /* _CONFIGURATOR_ */
