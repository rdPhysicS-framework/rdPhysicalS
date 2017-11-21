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

	void operator=(const RT_BRDF &other)
	{
		color.x = other.color.x;
		color.y = other.color.y;
		color.z = other.color.z;

		k = other.k;
		ex = other.ex;

		type = other.type;
	}
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

	void operator=(const RT_Material &other)
	{
		ambient = other.ambient;
		diffuse = other.diffuse;
		specular = other.specular;
		refl = other.refl;
	}
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

	void operator=(const RT_BBox &other)
	{
		x0 = other.x0; y0 = other.y0; z0 = other.z0;
		x1 = other.x1; y1 = other.y1; z1 = other.z1;
	}
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

	void operator=(const RT_Primitive &other)
	{
		p.x = other.p.x; p.y = other.p.y; p.z = other.p.z;
		s.x = other.s.x; s.y = other.s.y; s.z = other.s.z;
		r = other.r;
		material = other.material;
		type = other.type;
		invMatrix = other.invMatrix;
		bbox = other.bbox;
	}
};

enum RT_TypeLight
{
	RT_AMBIENT_LIGHT,
	RT_AREA_LIGHT,
	RT_POINT_LIGHT,
};

struct RT_Light
{
	RT_Vec3f position;
	RT_Vec3f color;
	float ls;
	float ex;

	RT_TypeLight type;

	void operator=(const RT_Light &other)
	{
		position.x = other.position.x;
		position.y = other.position.y;
		position.z = other.position.z;

		color.x = other.color.x;
		color.y = other.color.y;
		color.z = other.color.z;

		ls = other.ls;

		ex = other.ex;
	}
};

struct RT_ViewPlane
{
	int width;
	int height;
	RT_Vec2f sp;
	//RT_SScoord coord;

	void operator=(const RT_ViewPlane &other)
	{
		width = other.width;
		height = other.height;

		sp.x = other.sp.x;
		sp.y = other.sp.y;
	}
};

class RT_Camera
{
public:
	/*position*/
	RT_Vec3f eye;
	//RT_Vec3f lookAt;
	//RT_Vec3f up;

	float viewPlaneDistance;
	float zoom;

	//float rollAngle;
	//float exposureTime;

	RT_Vec3f u, v, w;

public:
	RT_Camera() {}
	RT_Camera(const RT_Vec3f &_eye, 
			  const float _viewPlaneDistance, 
			  const float _zoom, 
			  const RT_Vec3f &_u, 
			  const RT_Vec3f &_v, 
			  const RT_Vec3f &_w) :

		eye(_eye), 
		viewPlaneDistance(_viewPlaneDistance),
		zoom(_zoom),
		u(_u), v(_v), w(_w)
	{}

	void operator=(const RT_Camera &other)
	{
		eye.x = other.eye.x;
		eye.y = other.eye.y;
		eye.z = other.eye.z;

		viewPlaneDistance = other.viewPlaneDistance;
		zoom = other.zoom;

		u.x = other.u.x; u.y = other.u.y; u.z = other.u.z;
		v.x = other.v.x; v.y = other.v.y; v.z = other.v.z;
		w.x = other.w.x; w.y = other.w.y; w.z = other.w.z;
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

	void operator=(const RT_DataScene &other)
	{
		vp = other.vp;

		background.x = other.background.x;
		background.y = other.background.y;
		background.z = other.background.z;

		numLights = other.numLights;
		numObjects = other.numObjects;
	}
};

	PKG_END
RDPS_END

#endif //__OBJECTS_PACKAGE_H__