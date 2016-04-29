#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "Configurator.h"

namespace thermostat {

Configurator* Configurator::m_pInstance=NULL;  

Configurator* Configurator::Instance()
{
    if (!m_pInstance) { m_pInstance = new Configurator(); }

    return m_pInstance;
}

void Configurator::addFileData(const std::string& inConfigFile)
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

} /* namespace thermostat */
