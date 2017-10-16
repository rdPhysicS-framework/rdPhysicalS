#ifndef	__LOG_ERROR_H__
#define	__LOG_ERROR_H__

#include <stdexcept>
#include <string>


#include "../../GlobalDefs.h"

RDPS_BEGIN
	class LogError : public std::exception
	{
	public:
		explicit LogError(const std::string &message);
		explicit LogError(const char *message);
	};

	class Logger
	{
	private:
		static void GetErrorPlatformComponent(const int error, std::string msg);
		static void GetErrorDeviceComponent(const int error, std::string msg);
		static void GetErrorContextComponent(const int error, std::string msg);

	public:
		static void Log(const std::string message);
		static void Log(const int status, const std::string message);
	};
RDPS_END

#endif//__LOG_ERROR_H__