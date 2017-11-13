#ifndef	__OBJECTS_H__
#define	__OBJECTS_H__

#include "..\..\GlobalDefs.h"
#include "..\..\rdps-CL\Application\ClConfig.h"
#include <RTmath.h>

RDPS_BEGIN
	PKG_BEGIN

		//typedef cl_float3 RT_Vec3f;
		//typedef cl_float2 RT_Vec2f;

		enum RT_TypeBRDF
		{
			RT_GLOSSY_SPECULAR,
			RT_LAMBERTIAN,
			RT_PERFECT_SPECULAR
		};

		class RT_BRDF
		{
		private:
			RT::Vec4f color;
			float k;
			float exp;

			RT_TypeBRDF type;

		public:
			RT_BRDF();
			RT_BRDF(const RT::Vec4f &_color,
					const float _k,
					const float _ex,
				    const RT_TypeBRDF _type);

			RT_BRDF &operator=(const RT_BRDF &other);
		};

		class RT_Material
		{
		private:
			//RT_Vec3f color;
			/*float ambient;
			float diffuse;
			float specular;
			float intensity;*/

			RT_BRDF ambient;
			RT_BRDF diffuse;
			RT_BRDF specular;
			RT_BRDF refl;

		public:
			RT_Material();
			RT_Material(const RT_BRDF &_ambient,
						const RT_BRDF &_diffuse,
						const RT_BRDF &_specular,
						const RT_BRDF &_refl);

			RT_Material &operator=(const RT_Material &other);
		};

		enum RT_TypeObject
		{
			RT_BOX,
			RT_PLANE,
			RT_SPHERE
		};

		class RT_BBox
		{
		private:
			float x0, y0, z0;
			float x1, y1, z1;

		public:
			RT_BBox();
			RT_BBox(const float _x0, const float _y0, const float _z0,
				    const float _x1, const float _y1, const float _z1);

			RT_BBox &operator=(const RT_BBox &other);
		};

		class RT_Primitive
		{
		private:
			RT::Vec4f p;
			//RT_Vec3f p1, p2;
			/*box == size | plane == normal*/
			RT::Vec4f s;
			/*radius for sphere*/
			float r;

			RT_Material material;
			RT_TypeObject type;

			/*transform*/
			//float invMatrix[4][4];
			RT::Mat4f invMatrix;

			RT_BBox bbox;

		public:
			RT_Primitive();
			RT_Primitive(const RT::Vec4f &_p,
						 const RT::Vec4f &_s,
						 const float _r,
						 const RT_Material &_material,
						 const RT_TypeObject _type,
						 const RT::Mat4f &_invMatrix,
						 const RT_BBox &_bbox);

			RT_Primitive &operator=(const RT_Primitive &other);
		};

		enum RT_TypeLight
		{
			RT_AREA_LIGHT,
			RT_POINT_LIGHT
		};

		class RT_Light
		{
		private:
			RT::Vec4f position;
			RT::Vec4f color;
			float ls;
			float ex;

			RT_TypeLight type;

		public:
			RT_Light();
			RT_Light(const RT::Vec4f &_position,
					 const RT::Vec4f &_color,
					 const float _ls,
					 const float _ex);

			RT_Light &operator=(const RT_Light &other);
		};

		class RT_ViewPlane
		{
		private:
			int width;
			int height;
			RT::Vec4f sp;
			//RT_SScoord coord;

		public:
			RT_ViewPlane();
			RT_ViewPlane(const int _width,
						 const int _height,
					     const RT::Vec4f &_sp);

			RT_ViewPlane &operator=(const RT_ViewPlane &other);
		};

		class RT_Camera
		{
		private:
			/*position*/
			RT::Vec4f eye;
			RT::Vec4f lookAt;
			RT::Vec4f up;

			float viewPlaneDistance;
			float zoom;

			float rollAngle;
			float exposureTime;

			RT::Vec4f u, v, w;

		public:
			RT_Camera();
			RT_Camera(const RT::Vec4f &_eye,
					  const RT::Vec4f &_lookAt,
					  const RT::Vec4f &_up,
					  const float _viewPlaneDistance,
					  const float _zoom,
					  const float _rollAngle,
					  const float _exposureTime,
					  const RT::Vec4f &_u,
					  const RT::Vec4f &_v,
					  const RT::Vec4f &_w);

			RT_Camera &operator=(const RT_Camera &other);
		};

		class RT_DataScene
		{
		private:
			/*data of the canvas*/
			RT_ViewPlane vp;

			/*data of the camera(point of origin of the ray)*/
			//RT_Camera camera;

			/*background-color*/
			RT::Vec4f background;

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

		public:
			RT_DataScene();
			RT_DataScene(const RT_ViewPlane &_vp,
						 const RT::Vec4f &_background,
						 const int _numLights,
						 const int _numObjects);

			RT_DataScene &operator=(const RT_DataScene &other);
		};

	PKG_END
RDPS_END

#endif//__OBJECTS_H__