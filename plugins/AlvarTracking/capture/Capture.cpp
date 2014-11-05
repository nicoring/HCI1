#include "Capture.h"

using namespace mtq;

Capture::Capture(const Configuration config)
	: m_config(config)
{
}

Capture::~Capture()
{
}

const Configuration Capture::config() const
{
	return m_config;
}
