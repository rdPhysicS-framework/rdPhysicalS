#ifndef	__LOG_ERROR_H__
#define	__LOG_ERROR_H__

#include <stdexcept>
#include <string>
#include "../../GlobalDefs.h"

namespace rdps
{
	class LogError : public std::exception
	{
	public:
		explicit LogError(const std::string &message);
		explicit LogError(const char *message);
	};

	class Logger
	{
	private:
		static std::string GetErrorMessage(const InfoComponentCL componenet, const int codeError);
		static std::string GetErrorPlatformComponent(const int codeError);
		static std::string GetErrorPlatformInfo(const int codeError);
		static std::string GetErrorDeviceComponent(const int codeError);
		static std::string GetErrorDeviceInfo(const int codeError);
		static std::string GetErrorContextComponent(const int codeError);
		static std::string GetErrorContextInfo(const int codeError);
		static std::string GetErrorCommandQueueComponent(const int codeError);
		static std::string GetErrorCommandQueueInfo(const int codeError);

	public:
		static void Log(const std::string message);
		static void Log(const InfoComponentCL componenet, const int codeError, const std::string message);
	};

}

#endif//__LOG_ERROR_H__