#include "stdafx.h"
#include "Logger.h"

Logger::Logger(std::ostream *init) :
	_out_stream(init)
{
}

Logger::~Logger()
{
}

template<typename T>
Logger & Logger::operator<<(T const & value)
{
	if (_out_stream)
		*_out_stream << value;
}
