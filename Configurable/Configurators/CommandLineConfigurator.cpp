#include "CommandLineConfigurator.h"

#include <Language/Exception.hpp>

namespace Citra { namespace Configurable {

CommandLineConfigurator::CommandLineConfigurator(int argc, char* argv[])
 : IConfigurator(argc, argv)
{
    addData(argc, argv);
}

CommandLineConfigurator::~CommandLineConfigurator() { }

void CommandLineConfigurator::addData(int argc, char* argv[])
{
    std::cout << "Selected Configurations:" << std::endl;
	if (!argc % 2)
	{
		std::cerr << "bad num " << argc << " " << argc % 2 << std::endl;
		throw;
	}

	for (int i = 1; i + 1 < argc; i += 2)
	{
		std::cout << "  " << std::string(argv[i]) << " = " << std::string(argv[i + 1]) << std::endl;
		mConfigurations.push_back(Configuration(argv[i], argv[i + 1]));
	}
}

void CommandLineConfigurator::help(const std::string& inClassName, const std::string& inConfigName, const std::string& inType, const std::string& inDefaultValue)
{
    static bool first = true;

    if (first)
    {
        std::cout << "Configuration Options:" << std::endl;
        first = false;
    }

    bool init = isInitialised(inDefaultValue);
    std::cout << "  " << (init ? "OPTIONAL" : "REQUIRED");
    std::cout << " --" << inClassName << "::" << inConfigName;
    std::cout << " [" << inType;
    if (init)
    {
        std::cout << " = " << inDefaultValue;
    }
    std::cout << "]" << std::endl;
}

std::string CommandLineConfigurator::getValue(const std::string& inClassName, const std::string& inConfigName)
{
    for (const Configuration& aConfig : mConfigurations)
    {
        if (aConfig.Name == "--" + inClassName + "::" + inConfigName)
        {
            return aConfig.Value;
        }
    }

    THROW_RUNTIME_EXCEPTION("CommandLineConfigurator unknown configuration " << inClassName << "::" << inConfigName);
}


std::list<std::string> CommandLineConfigurator::getValues(const std::string& inClassName, const std::string& inConfigName)
{
    std::list<std::string> aResult;

    for (const Configuration& aConfig : mConfigurations)
    {
        if (aConfig.Name == "--" + inClassName + "::" + inConfigName)
        {
            aResult.push_back(aConfig.Value);
        }
    }
    return aResult;
}

} /* namespace Configurable*/ } /* namespace Citra */
