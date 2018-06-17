#ifndef _FILE_CONFIGURATOR_
#define _FILE_CONFIGURATOR_

#include <string>
#include <list>
#include <Configurable/IConfigurator.h>

namespace Citra { namespace Configurable {

class FileConfigurator : public IConfigurator
{
    public:
        FileConfigurator(int argc, char* argv[], const std::string& inConfigFile);
        virtual ~FileConfigurator();

        virtual void help(const std::string& inClassName, const std::string& inConfigName, const std::string& inType);

    protected:
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

        void addFileData(const std::string& inConfigFile);

        virtual std::string getValue(const std::string& inClassName, const std::string& inConfigName);
        virtual std::list<std::string> getValues(const std::string& inClassName, const std::string& inConfigName);

        std::list<Configuration> mConfigurations;

};

} /* namespace Configurable*/ } /* namespace Citra */

#endif /* _FILE_CONFIGURATOR_ */
