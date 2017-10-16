#ifndef	__LOG_ERROR_H__
#define	__LOG_ERROR_H__

#include <stdexcept>
#include <string>

namespace rdps
{
	class LogError : public std::logic_error
	{
	public:
		explicit LogError(const std::string &message);
		explicit LogError(const char *message);
	};

	class Logger
	{
	public:
		static void Log(const std::string message);
		static void Log(const int status, const std::string message);
	};

}

#endif//__LOG_ERROR_H__