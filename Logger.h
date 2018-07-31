#pragma once
#include "stdafx.h"

/* Logger class for printing game events to console; to be used like an output stream */

class Logger {
public:
	Logger(std::ostream *init);
	~Logger();

	template <typename T>
	Logger& operator<<(T const &value);

private:
	std::ostream *_out_stream;
};
