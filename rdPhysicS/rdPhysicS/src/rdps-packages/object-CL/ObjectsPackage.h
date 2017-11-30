#ifndef	 __OBJECTS_PACKAGE_H__
#define	 __OBJECTS_PACKAGE_H__

#include "..\..\rdps-CL\Application\ClConfig.h"
#include <RTmath.h>
#include "..\..\GlobalDefs.h"

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

		class RT_BRDF
		{
		public:
			RT_Vec3f RDPS_ALIGN(16) color;
			float RDPS_ALIGN(4) k;
			float RDPS_ALIGN(4) ex;

			RT_TypeBRDF RDPS_ALIGN(sizeof(RT_TypeBRDF)) type;

		public:
			RT_BRDF() :
				color(),
				k(0.0f),
				ex(0.0f)
			{}

			RT_BRDF(const RT_Vec3f &_color,
				const float _k,
				const float _ex,
				const RT_TypeBRDF _type) :
				color(_color),
				k(_k),
				ex(_ex),
				type(_type)
			{}

			friend std::ostream &operator<<(std::ostream &out, const RT_BRDF &brdf)
			{
				out << "color: " << brdf.color.x << " - " << brdf.color.y << " - " << brdf.color.z << std::endl;
				out << "k: " << brdf.k << std::endl;
				out << "ex: " << brdf.ex << std::endl;

				if (brdf.type == RT_GLOSSY_SPECULAR)
					out << "type: RT_GLOSSY_SPECULAR" << std::endl;
				if (brdf.type == RT_LAMBERTIAN)
					out << "type: RT_LAMBERTIAN" << std::endl;
				if (brdf.type == RT_PERFECT_SPECULAR)
					out << "type: RT_PERFECT_SPECULAR" << std::endl;

				return out;
			}
		};

		class RT_Material
		{
		public:
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
			RT_Material() {}

			RT_Material(const RT_BRDF &_ambient,
				const RT_BRDF &_diffuse,
				const RT_BRDF &_specular,
				const RT_BRDF &_refl) :
				ambient(_ambient),
				diffuse(_diffuse),
				specular(_specular),
				refl(_refl)
			{}

			friend std::ostream &operator<<(std::ostream &out, const RT_Material &m)
			{
				out << "\nMaterial" << std::endl;
				out << "AMBIENT" << m.ambient << std::endl;
				out << "DIFFUSE" << m.diffuse << std::endl;
				out << "SPECULAR" << m.specular << std::endl;
				out << "REFLECTIVE" << m.refl << std::endl;

				return out;
			}
		};

		enum RT_TypeObject
		{
			RT_BOX,
			RT_PLANE,
			RT_SPHERE
		};

		class RT_BBox
		{
		public:
			float RDPS_ALIGN(4) x0, y0, z0;
			float RDPS_ALIGN(4) x1, y1, z1;

		public:
			RT_BBox() :
				x0(0.0f), y0(0.0f), z0(0.0f),
				x1(0.0f), y1(0.0f), z1(0.0f)
			{}

			RT_BBox(const float _x0, const float _y0, const float _z0,
				const float _x1, const float _y1, const float _z1) :
				x0(_x0), y0(_y0), z0(_z0),
				x1(_x1), y1(_y1), z1(_z1)
			{}

			friend std::ostream &operator<<(std::ostream &out, const RT_BBox &b)
			{
				out << "\nBBox" << std::endl;
				out << "x0: " << b.x0 << " - y0: " << b.y0 << " - z0: " << b.z0 << std::endl;
				out << "x1: " << b.x1 << " - y1: " << b.y1 << " - z1: " << b.z1 << std::endl;

				return out;
			}
		};

		class RT_Primitive
		{
		public:
			RT_Vec3f RDPS_ALIGN(16) p;
			//RT_Vec3f p1, p2;
			/*box == size | plane == normal*/
			RT_Vec3f RDPS_ALIGN(16) s;
			/*radius for sphere*/
			float RDPS_ALIGN(4) r;

			RT_Material material;
			RT_TypeObject RDPS_ALIGN(sizeof(RT_TypeObject)) type;

			/*transform*/
			//float invMatrix[4][4];
			RT::Mat4f invMatrix;

			RT_BBox bbox;

		public:
			RT_Primitive()
			{}

			RT_Primitive(const RT_Vec3f &_p,
				const RT_Vec3f &_s,
				const float _r,
				const RT_Material &_material,
				const RT_TypeObject _type,
				const RT::Mat4f _invMatrix,
				const RT_BBox _bbox) :
				p(_p), s(_s), r(_r),
				material(_material),
				type(_type),
				invMatrix(_invMatrix),
				bbox(_bbox)
			{}

			friend std::ostream &operator<<(std::ostream &out, RT_Primitive &p)
			{
				if (p.type == RT_BOX)
					out << "BOX" << std::endl;
				else if (p.type == RT_PLANE)
					out << "PLANE" << std::endl;
				else if (p.type == RT_SPHERE)
					out << "SPHERE" << std::endl;

				out << "position: " << p.p.x << " - " << p.p.y << " - " << p.p.z << std::endl;
				out << "size_normal: " << p.s.x << " - " << p.s.y << " - " << p.s.z << std::endl;
				out << "r: " << p.r << std::endl;
				out << p.material;
				out << p.invMatrix;
				out << p.bbox << std::endl;

				return out;
			}
		};

		class RT_Emissive
		{
		public:
			int   RDPS_ALIGN(4) color;
			float RDPS_ALIGN(4) ls;

		public:
			RT_Emissive() : color(0), ls(0.0f) {}

			RT_Emissive(const int _color, 
						const float _ls) : 
				color(_color),
				ls(_ls)
			{}

			RT_Emissive(const RT_Emissive &other) :
				color(other.color),
				ls(other.ls)
			{}
		};

		typedef enum
		{
			RT_CIRCULAR,
			RT_RECTANGULAR
		} RT_TypeLamp;

		class RT_Lamp
		{
		public:
			RT::Vec4f RDPS_ALIGN(16) p;
			RT::Vec4f RDPS_ALIGN(16) a;
			RT::Vec4f RDPS_ALIGN(16) b;
			RT::Vec4f RDPS_ALIGN(16) normal;
			float RDPS_ALIGN(4) radius;
			RT_Emissive  material;

			RT_TypeLamp RDPS_ALIGN(4) type;

		public:
			RT_Lamp() {}

			RT_Lamp(const RT::Vec3f &_p,
					const RT::Vec3f &_a,
					const RT::Vec3f &_b,
					const RT::Vec3f &_normal,
					const float _radius,
					const RT_Emissive &_material,
					const RT_TypeLamp _type) :
				p(_p),
				a(_a),
				b(_b),
				normal(_normal),
				radius(_radius),
				material(_material),
				type(_type)
			{}

			RT_Lamp(const RT_Lamp &other) :
				p(other.p),
				a(other.a),
				b(other.b),
				normal(other.normal),
				radius(other.radius),
				material(other.material),
				type(other.type)
			{}

			RT_Lamp &operator=(const RT_Lamp &other)
			{
				p = other.p;
				a = other.a;
				b = other.b;
				normal = other.normal;
				radius = other.radius;
				material = other.material;
				type = other.type;

				return (*this);
			}
		};

		typedef enum
		{
			RT_AMBIENT_LIGHT,
			RT_AREA_LIGHT,
			RT_POINT_LIGHT
		} RT_TypeLight;

		class RT_Light
		{
		public:
			RT_Vec3f RDPS_ALIGN(16) point;
			RT_Vec3f RDPS_ALIGN(16) c_wi;
			
			float RDPS_ALIGN(4) ls;
			float RDPS_ALIGN(4) ex;
			int RDPS_ALIGN(4) index;

			RT_TypeLight RDPS_ALIGN(sizeof(RT_TypeLight)) type;

		public:
			RT_Light() {}

			RT_Light(const RT_Vec3f &_point,
					 const RT_Vec3f &_c_wi,
					 const float _ls,
					 const float _ex,
					 const int _index,
					 const RT_TypeLight _type) :
				point(_point),
				c_wi(_c_wi),
				ls(_ls),
				ex(_ex),
				index(_index),
				type(_type)
			{}

			RT_Light &operator=(const RT_Light &other)
			{
				point = other.point;
				c_wi = other.c_wi;
				ls = other.ls;
				ex = other.ex;
				type = other.type;
				return (*this);
			}

			friend std::ostream &operator<<(std::ostream &out, RT_Light &l)
			{
				if (l.type == RT_AMBIENT_LIGHT)
					out << "RT_AMBIENT_LIGHT" << std::endl;
				else if (l.type == RT_POINT_LIGHT)
					out << "RT_POINT_LIGHT" << std::endl;


				out << "position: " << l.point.x << " - " << l.point.y << " - " << l.point.z << std::endl;
				out << "color: " << l.c_wi.x << " - " << l.c_wi.y << " - " << l.c_wi.z << std::endl;
				out << "ls: " << l.ls << std::endl;
				out << "ex: " << l.ex << std::endl << std::endl;
				out << "type: " << l.type << std::endl;
				return out;
			}
		};

		class RT_ViewPlane
		{
		public:
			int RDPS_ALIGN(4) width;
			int RDPS_ALIGN(4) height;
			RT_Vec2f RDPS_ALIGN(8) sp;
			//RT_SScoord coord;

		public:
			RT_ViewPlane() : width(0), height(0), sp() {}

			RT_ViewPlane(const int w,
				         const int h,
				         const RT_Vec2f &_sp) : width(w), height(h), sp(_sp) {}

			/*friend std::ostream &operator<<(std::ostream &out, RT_ViewPlane &vp)
			{
			out << "ViewPlane" << std::endl;
			out << "size_pixel: " << vp.sp.x << " - " << vp.sp.y << std::endl;
			out << "width: " << vp.width << std::endl;
			out << "height: " << vp.height << std::endl;

			return out;
			}*/
		};

		class RT_Camera
		{
		public:
			/*position*/
			RT_Vec3f RDPS_ALIGN(16) eye;
			//RT_Vec3f lookAt;
			//RT_Vec3f up;

			float RDPS_ALIGN(4) viewPlaneDistance;
			float RDPS_ALIGN(4) zoom;

			//float rollAngle;
			//float exposureTime;

			RT_Vec3f RDPS_ALIGN(16) u;
			RT_Vec3f RDPS_ALIGN(16) v;
			RT_Vec3f RDPS_ALIGN(16) w;

		public:
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

			friend std::ostream &operator<<(std::ostream &out, RT_Camera &c)
			{
				out << "Camera" << std::endl;
				out << "eye: " << c.eye.x << " - " << c.eye.y << " - " << c.eye.z << std::endl;
				out << "viewPlaneDistance: " << c.viewPlaneDistance << std::endl;
				out << "zoom: " << c.zoom << std::endl;
				out << "U: " << c.u.x << " - " << c.u.y << " - " << c.u.z << std::endl;
				out << "V: " << c.v.x << " - " << c.v.y << " - " << c.v.z << std::endl;
				out << "W: " << c.w.x << " - " << c.w.y << " - " << c.w.z << std::endl << std::endl;

				return out;
			}
		};

		typedef enum
		{
			RT_HAMMERSLEY,
			RT_JITTERED,
			RT_REGULAR
		} RT_TypeSampler;

		typedef enum
		{
			RT_AREA_LIGHTING,
			RT_RAYCASTING
		} RT_TypeTracer;

		class RT_DataScene
		{
		public:
			/*data of the canvas*/
			RT_ViewPlane vp;

			/*data of the camera(point of origin of the ray)*/
			//RT_Camera camera;

			/*background-color*/
			RT_Vec3f RDPS_ALIGN(16) background;

			/*data of the lights*/
			int RDPS_ALIGN(4) numLights;

			/*data of the lights*/
			int RDPS_ALIGN(4) numLamps;

			/*data of the objects*/
			int RDPS_ALIGN(4) numObjects;

			/*data of the samples*/
			int RDPS_ALIGN(4) numSamples;
			int RDPS_ALIGN(4) numSets;
			/*int jump;
			ulong count;
			ulong numShuffledIndices;
			/*seed random*/
			uint RDPS_ALIGN(4) seed;

			RT_TypeSampler RDPS_ALIGN(sizeof(RT_TypeSampler)) type;
			RT_TypeTracer  RDPS_ALIGN(sizeof(RT_TypeTracer)) typeTracer;

		public:
			RT_DataScene() :
				vp(),
				background(),
				numLights(0),
				numObjects(0),
				numSamples(0),
				numSets(0),
				seed(0)
			{}

			RT_DataScene(const RT_ViewPlane &_vp,
						 const RT_Vec3f &_background,
						 const int _numLights,
						 const int _numLamps,
						 const int _numObjects,
						 const int _numSamples,
						 const int _numSets,
						 RT_TypeSampler _type,
						 RT_TypeTracer _typeTracer,
						 const uint _seed) :
				vp(_vp), background(_background),
				numLights(_numLights),
				numLamps(_numLamps),
				numObjects(_numObjects),
				numSamples(_numSamples),
				numSets(_numSets),
				type(_type),
				typeTracer(_typeTracer),
				seed(_seed)
			{}

			/*friend std::ostream &operator<<(std::ostream &out, RT_DataScene &ds)
			{
			out << "DataScene" << std::endl;
			out << ds.vp;
			out << "background: " << ds.background.x << " - " << ds.background.y << " - " << ds.background.z << std::endl;
			out << "numLights: " << ds.numLights << std::endl;
			out << "numObjects: " << ds.numObjects << std::endl;
			out << "numSamples: " << ds.numSamples << std::endl;
			out << "numSets: " << ds.numSets << std::endl;
			out << "seed: " << ds.seed << std::endl;

			return out;
			}*/
		};

	PKG_END
RDPS_END

#endif //__OBJECTS_PACKAGE_H__