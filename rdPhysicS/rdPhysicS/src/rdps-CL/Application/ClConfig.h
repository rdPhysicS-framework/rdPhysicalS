#ifndef	__CL_CONFIG_H__
#define	__CL_CONFIG_H__

#include <string>
#include <vector>

#ifdef APPLE
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
//#include<CL/cl.hpp>
#endif // APPLE

#endif//__CL_CONFIG_H__