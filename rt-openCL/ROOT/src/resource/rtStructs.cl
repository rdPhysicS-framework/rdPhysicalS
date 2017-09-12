#ifndef	 __RT_STRUCTS_CL
#define	 __RT_STRUCTS_CL

/*----------------------------------------------------------------------------------------------
 *
 * RT_BRDF
 * data for material Phong
 * Lambertian(ambient), Lambertian(diffuse), GlossySpecular(specular)
 *----------------------------------------------------------------------------------------------*/
typedef struct __attribute__((package))
{ 
	RT_Vec3f color;
	float k;
	float index;

	RT_TypeBRDF type;
}	RT_BRDF;

typedef struct __attribute__((package))
{ 
	float k;
	float ior;

	RT_TypeBTDF type;
} RT_BTDF;

typedef struct __attribute__((package))
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

/*----------------------------------------------------------------------------------------------
 *
 * RT_Primitives
 * Box, Plane, Sphere
 *----------------------------------------------------------------------------------------------*/
typedef struct __attribute__((package))
{ 
	RT_Vec3f p;
	//RT_Vec3f p1, p2;
	/*box == size | plane == normal*/
	RT_Vec3f s_n;
	/*radius for sphere*/
	float r;

	RT_Material material;
	RT_TypeObject type;

	/*transform*/
	RT_Mat4f invMatrix;
} RT_Primitive;

/*----------------------------------------------------------------------------------------------
 *
 * RT_Result
 * data of the results of the collisions
 *----------------------------------------------------------------------------------------------*/
typedef struct __attribute__((package))
{
	bool hit;
	float t;
	RT_Vec3f lhitPoint;
	RT_Vec3f normal;
	RT_Material material;
	int depth;
} RT_Result;

/*----------------------------------------------------------------------------------------------
 *
 * RT_Light
 * data of the lights PointLight
 *----------------------------------------------------------------------------------------------*/
typedef struct __attribute__((package))
{
	RT_Vec3f position;
	RT_Vec3f color;
	float ls;
	float ex;

	RT_TypeLight type;
} RT_Light;

/*----------------------------------------------------------------------------------------------
 *
 * RT_ViewPlane
 * data of the world
 *----------------------------------------------------------------------------------------------*/
/*Data of Canvas*/
typedef struct __attribute__((package))
{
	int width;
	int height;
	RT_Vec2f sp;
	//RT_SScoord coord;
} RT_ViewPlane;

/*
 *Data of camera.
 *Pinhole
*/
typedef struct __attribute__((package))
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
} RT_Camera;


typedef struct __attribute__((package))
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

/*----------------------------------------------------------------------------------------------
 *
 * Result
 *
 *----------------------------------------------------------------------------------------------*/
inline RT_Result CreateResult();

/*----------------------------------------------------------------------------------------------
 *
 * methods for the material
 *
 *----------------------------------------------------------------------------------------------*/
RT_Vec3f Lambertian_F(const RT_BRDF *brdf);
RT_Vec3f Lambertian_RHO(const RT_BRDF *brdf);
RT_Vec3f GlossySpecular_F(const RT_Result *r, 
						  const RT_Vec3f *wi,
						  const RT_Vec3f *wo);
RT_Vec3f PerfectSpecular_SampleF(const RT_Result *r, 
								 RT_Vec3f *wi,
								 const RT_Vec3f *wo);

/*----------------------------------------------------------------------------------------------
 *
 * it calculates the effects of the light in the material
 * 
 *----------------------------------------------------------------------------------------------*/

RT_Vec3f Shade(__global const RT_Light *lights,
			   __constant RT_Primitive *objects,
			   __constant RT_DataScene *world,
			   const RT_Ray *ray,
			   const RT_Result *r);

/*----------------------------------------------------------------------------------------------
 *
 * Methods to verify intercession with the sphere
 *
 *----------------------------------------------------------------------------------------------*/
bool Sphere_Hit(const RT_Primitive *s, 
				const RT_Ray *ray, 
				float *tmin, RT_Result *r);
bool Sphere_ShadowHit(const RT_Primitive *s, 
					  const RT_Ray *ray, float *tmin);

/*----------------------------------------------------------------------------------------------
 *
 * Methods to verify intercession with the Plane
 *
 *----------------------------------------------------------------------------------------------*/
 bool Plane_Hit(const RT_Primitive *p, 
				const RT_Ray *ray, 
				float *tmin, RT_Result *r);
 bool Plane_ShadowHit(const RT_Primitive *p, 
					  const RT_Ray *ray, 
					  float *tmin);

/*----------------------------------------------------------------------------------------------
 *
 * Methods to verify intercession with the Cube
 *
 *----------------------------------------------------------------------------------------------*/
 RT_Vec3f Box_Normal(const RT_Primitive *b, 
					 const RT_Vec3f *p);
 bool Box_Hit(const RT_Primitive *b, 
			  const RT_Ray *ray, 
			  float *tmin, RT_Result *r);
 bool Box_ShadowHit(const RT_Primitive *b, 
					const RT_Ray *ray, 
					float *tmin);

/*----------------------------------------------------------------------------------------------
 *
 * Method that verifies collision of transformed objects
 *
 *----------------------------------------------------------------------------------------------*/
 bool Instance_Hit(const RT_Primitive *object,
				   const RT_Ray *ray,
				   float *tmin,
				   RT_Result *r); 
 bool Instance_ShadowHit(const RT_Primitive *object, 
						 const RT_Ray *ray, 
						 float *tmin); 

/*----------------------------------------------------------------------------------------------
 *
 * Methods for the lights
 *
 *----------------------------------------------------------------------------------------------*/
RT_Light Create_PointLight(const RT_Vec3f p, 
						   const RT_Vec3f c, 
						   const float ls);
inline RT_Vec3f Direction(const RT_Light *l, 
						  const RT_Result *r);
inline RT_Vec3f Color(const RT_Light *l, 
					  const RT_Result *r);
bool InShadow(const RT_Light *l, 
			  __constant RT_Primitive *objects,
			  const int numObj, 
			  const RT_Ray ray);

/*----------------------------------------------------------------------------------------------
 *
 * The direction of the ray returns based on the camera
 *
 *----------------------------------------------------------------------------------------------*/
inline RT_Vec3f GetDirectionRayCam(const RT_Vec2f *point, const RT_Camera *camera);

/*----------------------------------------------------------------------------------------------
 *
 * Method for collision verification between the rays and objects
 *
 *----------------------------------------------------------------------------------------------*/
RT_Result Hit(__constant RT_Primitive *objects, 
			  const int numObj, const RT_Ray *ray);
bool ShadowHit(__constant RT_Primitive *objects, 
			   const int numObj, const RT_Ray *ray, 
			   float tmin);

/*----------------------------------------------------------------------------------------------
 *
 * Method for the Tracer
 *
 *----------------------------------------------------------------------------------------------*/
RT_Vec3f TraceRay(__global const RT_Light *lights,
				  __constant RT_Primitive *objects,
				  __constant RT_DataScene *world, 
				  const RT_Ray *ray);
#endif //__RT_STRUCTS_CL