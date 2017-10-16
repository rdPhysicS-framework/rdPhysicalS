#include "LogError.h"

rdps::LogError::LogError(const std::string &message) :
	std::logic_error(message.c_str())
{}

rdps::LogError::LogError(const char *message) :
	std::logic_error(message)
{}

void rdps::Logger::Log(const std::string message)
{
	throw LogError(message);
}
