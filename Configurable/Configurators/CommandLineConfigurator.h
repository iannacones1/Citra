#ifndef _COMMAND_LINE_CONFIGURATOR_
#define _COMMAND_LINE_CONFIGURATOR_

#include <string>
#include <list>
#include <Configurable/IConfigurator.h>

namespace Citra { namespace Configurable {

class CommandLineConfigurator : public IConfigurator
{
    public:
        CommandLineConfigurator(int argc, char* argv[]);
        virtual ~CommandLineConfigurator();

        virtual void help(const std::string& inClassName, const std::string& inConfigName, const std::string& inType, const std::string& inDefaultValue) override;

    protected:
        struct Configuration
        {
          Configuration(const std::string& inName,
                        const std::string& inValue)
           : Name(inName), Value(inValue)
          { }

          std::string Name;
          std::string Value;
        };

        void addData(int argc, char* argv[]);

        virtual std::string getValue(const std::string& inClassName, const std::string& inConfigName);
        virtual std::list<std::string> getValues(const std::string& inClassName, const std::string& inConfigName);

        std::list<Configuration> mConfigurations;
};

} /* namespace Configurable*/ } /* namespace Citra */

#endif /* _COMMAND_LINE_CONFIGURATOR_ */
