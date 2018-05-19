#include "IConfigurator.h"

namespace Citra { namespace Configurable {

IConfigurator* IConfigurator::m_pInstance = NULL;

IConfigurator::IConfigurator()
{
	if (m_pInstance)
	{
		std::cerr << "CANNOT HAVE MULTIPLE CONFIGURATORS" << std::endl;
		throw;
	}
	m_pInstance = this;
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

} /* namespace Configurable*/ } /* namespace Citra */
