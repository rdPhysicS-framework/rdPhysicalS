#include "ProgramComponent.h"
#include "ContextComponent.h"
#include "DeviceComponent.h"
#include "..\Util\Details.h"
#include "..\Util\LogError.h"

USING_RDPS
USING_CL

std::string ProgramComponent::GetBuidInfo(const DeviceComponent &device, 
													const cl_program_build_info paramName)
{
	return Details::DisplayBuildInfo(*this, device, paramName);
}

ProgramComponent::ProgramComponent() :
		  BaseClComponent<Type>()
{}

ProgramComponent::ProgramComponent(const ContextComponent &context, 
											 const std::string source, 
											 const std::string options) :
		  BaseClComponent<Type>()
{
	int status = 0;
	const char *s = source.c_str();
	size_t size = source.size();
	object = clCreateProgramWithSource(context(), 1, (const char**)&s, (const size_t*)&size, &status);
	/*importante tratar erro*/
}

ProgramComponent::ProgramComponent(const cl_program &program) :
				   BaseClComponent<Type>(program)
{}

ProgramComponent::ProgramComponent(const ProgramComponent &other) :
				   BaseClComponent<Type>(other)
{}

ProgramComponent::~ProgramComponent()
{
	Release();
}

void ProgramComponent::Release()
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

void ProgramComponent::Retain()
{
	if (object)
	{
		if (int status = clRetainProgram(object) != CL_SUCCESS)
		{
			Logger::Log("ERROR: " + std::to_string(status));
		}
	}
}

std::string ProgramComponent::GetInfo(const cl_program_info paramName)
{
	return std::string();
}

ProgramComponent &ProgramComponent::BuildProgram(const DeviceComponent &device,
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
