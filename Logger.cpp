#include "stdafx.h"
#include "Logger.h"

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::write(std::string msg)
{
	std::cout << msg << std::endl;
}
