#include "ProgramComponente.h"
#include "ContextComponente.h"
#include "DeviceComponente.h"
#include "..\Util\Details.h"
#include "..\Util\LogError.h"

USING_RDPS
USING_CL

std::string ProgramComponente::GetBuidInfo(const DeviceComponente &device, 
													const cl_program_build_info paramName)
{
	return Details::DisplayBuildInfo(*this, device, paramName);
}

ProgramComponente::ProgramComponente() :
		  BaseClComponente<Type>()
{}

ProgramComponente::ProgramComponente(const ContextComponente &context, 
											 const std::string source, 
											 const std::string options) :
		  BaseClComponente<Type>()
{
	int status = 0;
	const char *s = source.c_str();
	size_t size = source.size();
	object = clCreateProgramWithSource(context(), 1, (const char**)&s, (const size_t*)&size, &status);
	/*importante tratar erro*/
}

ProgramComponente::ProgramComponente(const cl_program &program) :
				   BaseClComponente<Type>(program)
{}

ProgramComponente::ProgramComponente(const ProgramComponente &other) :
				   BaseClComponente<Type>(other)
{}

ProgramComponente::~ProgramComponente()
{
	Release();
}

void ProgramComponente::Release()
{
	if (object)
	{
		if (int status = clReleaseProgram(object) != CL_SUCCESS)
		{
			Logger::Log("ERROR: " + std::to_string(status));
		}

		object = nullptr;
	}
}

void ProgramComponente::Retain()
{
	if (object)
	{
		if (int status = clRetainProgram(object) != CL_SUCCESS)
		{
			Logger::Log("ERROR: " + std::to_string(status));
		}
	}
}

std::string ProgramComponente::GetInfo(const cl_program_info paramName)
{
	return std::string();
}

ProgramComponente &ProgramComponente::BuildProgram(const DeviceComponente &device,
												   const std::string &options)
{
	cl_device_id id = device();
	const char *o = options.c_str();
	if (int status = clBuildProgram(object, 1, &id,
									o, 
									nullptr,
									nullptr         ) 
		!= CL_SUCCESS                               )
	{
		Logger::Log("ERROR when building the program. \nERROR: "
					+ std::to_string(status) + "\n\n" 
					"Information of the ERROR in the openCl" +
					GetBuidInfo(device, CL_PROGRAM_BUILD_LOG));
	}

	return (*this);
}
