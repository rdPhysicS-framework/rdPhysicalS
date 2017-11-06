#ifndef	 __OBJECTS_PACKAGE_H__
#define	 __OBJECTS_PACKAGE_H__

#include "..\..\GlobalDefs.h"
#include "..\..\rdps-CL\Application\ClConfig.h"
#include <RTmath.h>

RDPS_BEGIN
	PKG_BEGIN
	
typedef cl_float3 RT_Vec3f;
typedef cl_float2 RT_Vec2f;

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

inline float clamp(double x, double min, double max)
{
	return static_cast<float>((x < min) ? min : (x > max) ? max : x);
}

/*std::ostream &operator<<(std::ostream &out, const RT_Vec3f &v)
{
out << "(" << v.x << " - " << v.y << " - " << v.z << ")" << std::endl;
return out;
}*/

enum RT_TypeBRDF
{
	RT_GLOSSY_SPECULAR,
	RT_LAMBERTIAN,
	RT_PERFECT_SPECULAR
};

struct RT_BRDF
{
	RT_Vec3f color;
	float k;
	float ex;

	RT_TypeBRDF type;
};

struct RT_Material
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
};

enum RT_TypeObject
{
	RT_BOX,
	RT_PLANE,
	RT_SPHERE
};

struct RT_BBox
{
	float x0, y0, z0;
	float x1, y1, z1;
};

struct RT_Primitive
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
	//float invMatrix[4][4];
	RT::Mat4f invMatrix;

	RT_BBox bbox;
};

enum RT_TypeLight
{
	RT_AREA_LIGHT,
	RT_POINT_LIGHT
};

struct RT_Light
{
	RT_Vec3f position;
	RT_Vec3f color;
	float ls;
	float ex;

	RT_TypeLight type;
};

struct RT_ViewPlane
{
	int width;
	int height;
	RT_Vec2f sp;
	//RT_SScoord coord;
};

struct RT_Camera
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
};

struct RT_DataScene
{
	/*data of the canvas*/
	RT_ViewPlane vp;

	/*data of the camera(point of origin of the ray)*/
	//RT_Camera camera;

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
};

	PKG_END
RDPS_END

#endif //__OBJECTS_PACKAGE_H__