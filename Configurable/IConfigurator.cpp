#include "IConfigurator.h"

namespace Citra { namespace Configurable {

IConfigurator* IConfigurator::m_pInstance = NULL;

IConfigurator::IConfigurator(int argc, char* argv[]) : mHelp(false)
{
	if (m_pInstance)
	{
		std::cerr << "CANNOT HAVE MULTIPLE CONFIGURATORS" << std::endl;
		throw;
	}
	m_pInstance = this;

    for (int i = 0; i < argc; i++)
    {
        mHelp |= (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help");
    }
}

IConfigurator::~IConfigurator()
{
    m_pInstance = NULL;
}

IConfigurator* IConfigurator::Instance()
{
	if (!m_pInstance)
	{
		std::cerr << "SOMEBODY FORGOT TO MAKE A CONFIGURATOR" << std::endl;
		throw;
	}
	return m_pInstance;
}

bool IConfigurator::help()
{
    return Instance()->mHelp;
}

} /* namespace Configurable*/ } /* namespace Citra */
