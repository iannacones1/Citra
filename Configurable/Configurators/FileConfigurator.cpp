#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

#include "FileConfigurator.h"

namespace Citra { namespace Configurable {

FileConfigurator::FileConfigurator(int argc, char* argv[], const std::string& inConfigFile)
 : IConfigurator(argc, argv)
{
    addFileData(inConfigFile);
}

FileConfigurator::~FileConfigurator() { }

void FileConfigurator::addFileData(const std::string& inConfigFile)
{
    std::ifstream infile(inConfigFile);
    std::string line;

    while (std::getline(infile, line))
    {
        if (line.empty()) { continue; }

        std::istringstream iss(line);

        std::vector<std::string> ret{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};

        if (ret.at(0) == "CONFIG")
        {
            addFileData(ret.at(1));
        }
        else
        {
            mConfigurations.push_back(Configuration(ret.at(0), ret.at(1), ret.at(2)));
        }
    }
}

void FileConfigurator::help(const std::string& inClassName, const std::string& inConfigName, const std::string& inType)
{
    std::cout << " OPTION: " << inClassName << " " << inConfigName << " '" << inType << "'" << std::endl;
}

std::string FileConfigurator::getValue(const std::string& inClassName, const std::string& inConfigName)
{
    for (const Configuration& aConfig : mConfigurations)
    {
        if (aConfig.Source == inClassName && aConfig.Name == inConfigName)
        {
            return aConfig.Value;
        }
    }
    std::stringstream ss;
    ss << "FileConfigurator unknown configuration " << inClassName << "::" << inConfigName;
    throw std::runtime_error(ss.str());
}


std::list<std::string> FileConfigurator::getValues(const std::string& inClassName, const std::string& inConfigName)
{
    std::list<std::string> aResult;

    for (const Configuration& aConfig : mConfigurations)
    {
        if (aConfig.Source == inClassName && aConfig.Name == inConfigName)
        {
            aResult.push_back(aConfig.Value);
        }
    }
    return aResult;
}

} /* namespace Configurable*/ } /* namespace Citra */
