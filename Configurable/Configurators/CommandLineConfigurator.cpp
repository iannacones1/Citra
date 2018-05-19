#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "CommandLineConfigurator.h"

namespace Citra { namespace Configurable {

CommandLineConfigurator::CommandLineConfigurator(int argc, char* argv[]) { addData(argc, argv); }
CommandLineConfigurator::~CommandLineConfigurator() { }

void CommandLineConfigurator::addData(int argc, char* argv[])
{
	if (!argc % 2)
	{
		std::cerr << "bad num " << argc << " " << argc % 2 << std::endl;
		throw;
	}

	for (int i = 1; i + 1 < argc; i += 2)
	{
		std::cout << std::string(argv[i]) << " = " << std::string(argv[i + 1]) << std::endl;
		mConfigurations.push_back(Configuration(argv[i], argv[i + 1]));
	}
}

std::string CommandLineConfigurator::getValue(const std::string& inClassName, const std::string& inConfigName)
{
    for (const Configuration& aConfig : mConfigurations)
    {
        if (aConfig.Name == inClassName + "::" + inConfigName)
        {
            return aConfig.Value;
        }
    }
    std::cerr << "CommandLineConfigurator unknown configuration " << inClassName << "::" << inConfigName << std::endl;
    throw;
}


std::list<std::string> CommandLineConfigurator::getValues(const std::string& inClassName, const std::string& inConfigName)
{
    std::list<std::string> aResult;

    for (const Configuration& aConfig : mConfigurations)
    {
        if (aConfig.Name == inClassName + "::" + inConfigName)
        {
            aResult.push_back(aConfig.Value);
        }
    }
    return aResult;
}

} /* namespace Configurable*/ } /* namespace Citra */
