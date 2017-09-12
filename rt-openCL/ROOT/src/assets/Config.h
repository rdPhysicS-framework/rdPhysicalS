#ifndef	__CONFIG_H__
#define	__CONFIG_H__

#include <iostream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <RTmath.h>

#ifdef APPLE
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#include<CL/cl.hpp>
#endif // APPLE

#define PATH "src/resource/"
#define FILE_NAME "raytrace.png"

#define NAME_NUM 4
#define DATA_NUM 21
#define WINDOW_SIZE 13
#define MAX_SOURCE_SIZE 0x100000

#define WIDTH_CANVAS 1920
#define HEIGHT_CANVAS 1080

typedef cl_float3 RT_Vec3f;
typedef cl_float2 RT_Vec2f;

typedef unsigned __int32 uint;
typedef unsigned __int64 ulong;

inline RT_Vec3f operator+(const RT_Vec3f &v1, const RT_Vec3f &v2)
{
	return{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

inline RT_Vec3f operator-(const RT_Vec3f &v1, const RT_Vec3f &v2)
{
	return{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

inline RT_Vec3f Cross(const RT_Vec3f &v1, const RT_Vec3f &v2)
{
	return{ (v1.y * v2.z) - (v1.z * v2.y),
		(v1.z * v2.x) - (v1.x * v2.z),
		(v1.x * v2.y) - (v1.y * v2.x) };
}

inline RT_Vec3f Normalize(const RT_Vec3f &v)
{
	float invSize = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return{ v.x * invSize, v.y * invSize, v.z * invSize };
}

/*std::ostream &operator<<(std::ostream &out, const RT_Vec3f &v)
{
	out << "(" << v.x << " - " << v.y << " - " << v.z << ")" << std::endl;
	return out;
}*/

struct Program {
	cl_platform_id platform;
	cl_device_id device;
	cl_context context;
	cl_command_queue queue;
	cl_program program;

	Program() : platform(nullptr),
		        device(nullptr),
		        queue(nullptr),
		        program(nullptr) {}
	~Program() 
	{
		cl_int status;
		status = clReleaseProgram(program);
		//ret = clReleaseDevice(device);
		status = clReleaseCommandQueue(queue);
		status = clReleaseContext(context);
	}

	void BildProgram()
	{
		cl_int status;
		status = clBuildProgram(program, 1, &device, 
							    nullptr, nullptr, nullptr);
		if (status != CL_SUCCESS)
		{
			std::cerr << "Error during conpilation OpenCl code: "
					  << status << std::endl;
		}
		/*caso houver tratar erro*/
	}
};

typedef enum
{
	RT_GLOSSY_SPECULAR,
	RT_LAMBERTIAN,
	RT_PERFECT_SPECULAR
} RT_TypeBRDF;

typedef struct
{
	RT_Vec3f color;
	float k;
	float ex;

	RT_TypeBRDF type;
}	RT_BRDF;

typedef struct
{
	//RT_Vec3f color;
	/*float ambient;
	float diffuse;
	float specular;
	float intensity;*/

	RT_BRDF ambient;
	RT_BRDF diffuse;
	RT_BRDF specular;
	RT_BRDF refl;
} RT_Material;

typedef enum
{
	RT_BOX,
	RT_PLANE,
	RT_SPHERE
} RT_TypeObject;

typedef struct
{
	RT_Vec3f p;
	//RT_Vec3f p1, p2;
	/*box == size | plane == normal*/
	RT_Vec3f s;
	/*radius for sphere*/
	float r;

	RT_Material material;
	RT_TypeObject type;

	/*transform*/
	float invMatrix[4][4];
} RT_Primitive;

typedef enum
{
	RT_AREA_LIGHT,
	RT_POINT_LIGHT
} RT_TypeLight;

typedef struct
{
	RT_Vec3f position;
	RT_Vec3f color;
	float ls;
	float ex;

	RT_TypeLight type;
} RT_Light;

typedef struct
{
	int width;
	int height;
	RT_Vec2f sp;
	//RT_SScoord coord;
} RT_ViewPlane;

typedef struct
{
	/*position*/
	RT_Vec3f eye;
	RT_Vec3f lookAt;
	RT_Vec3f up;

	float viewPlaneDistance;
	float zoom;

	float rollAngle;
	float exposureTime;

	RT_Vec3f u, v, w;

	void computeUVW()
	{
		w = Normalize(eye - lookAt);

		if (eye.x == lookAt.x && eye.z == lookAt.z && eye.y > lookAt.y)
		{
			u = { 0, 0, 1 };
			v = { 1, 0, 0 };
			w = { 0, 1, 0 };
			return;
		}

		if (eye.x == lookAt.x && eye.z == lookAt.z && eye.y < lookAt.y)
		{
			u = { 1, 0, 0 };
			v = { 0, 0, 1 };
			w = { 0, -1, 0 };
			return;
		}

		u = Normalize(Cross(up, w));
		v = Normalize(Cross(w, u));
	}
} RT_Camera;

typedef struct
{
	/*data of the canvas*/
	RT_ViewPlane vp;

	/*data of the camera(point of origin of the ray)*/
	RT_Camera camera;

	/*background-color*/
	RT_Vec3f background;

	/*data of the lights*/
	int numLights;

	/*data of the objects*/
	int numObjects;

	/*data of the samples*/
	/*int numSamples;
	int numSets;
	int jump;
	ulong count;
	ulong numShuffledIndices;
	/*seed random*/
	/*ulong seed;*/
} RT_DataScene;

/*struct RT_Program {
	cl::Device device;
	cl::Context context;
	cl::CommandQueue queue;
	cl::Program program;

	~RT_Program()
	{
		/*cl_int status;
		status = clReleaseProgram(program);
		//ret = clReleaseDevice(device);
		status = clReleaseCommandQueue(queue);
		status = clReleaseContext(context);*/
	/*}

	void BildProgram()
	{
		cl_int status = program.build({ device });
		if (status)
		{
			std::cerr << "Error during conpilation OpenCl code: "
				<< status << std::endl;
		}
	}
};*/

#endif//__CONFIG_H__
