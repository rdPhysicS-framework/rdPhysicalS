#ifndef	__LOG_ERROR_H__
#define	__LOG_ERROR_H__

#include <stdexcept>
#include <string>
#include "..\GlobalDefs.h"

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
		static char *GetErrorMessage(const InfoComponentCL componenet, const int codeError);
		static char *GetErrorPlatformComponent(const int codeError);
		static char *GetErrorPlatformInfo(const int codeError);
		static char *GetErrorDeviceComponent(const int codeError);
		static char *GetErrorDeviceInfo(const int codeError);
		static char *GetErrorContextComponent(const int codeError);
		static char *GetErrorContextInfo(const int codeError);
		static char *GetErrorCommandQueueComponent(const int codeError);
		static char *GetErrorCommandQueueInfo(const int codeError);
		static char *GetErrorProgramComponent(const int codeError);
		static char *GetErrorProgramInfo(const int codeError);
		static char *GetErrorProgramBuildInfo(const int codeError);
	public:
		static void Log(const std::string message);
		static void Log(const InfoComponentCL componenet, const int codeError, const std::string message);
	};

}

#endif//__LOG_ERROR_H__