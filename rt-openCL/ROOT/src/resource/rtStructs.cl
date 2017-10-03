/*----------------------------------------------------------------------------------------------
 *
 * RT_BRDF
 * data for material Phong
 * Lambertian(ambient), Lambertian(diffuse), GlossySpecular(specular)
 *----------------------------------------------------------------------------------------------*/
typedef struct
{ 
	RT_Vec3f color;
	float k;
	float index;

	RT_TypeBRDF type;
}	RT_BRDF;

typedef struct
{ 
	float k;
	float ior;

	RT_TypeBTDF type;
} RT_BTDF;

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

/*----------------------------------------------------------------------------------------------
 *
 * Bounding Box
 * 
 *----------------------------------------------------------------------------------------------*/

typedef struct
{ 
	float x0, y0, z0;
	float x1, y1, z1;
} RT_BBox;

/*----------------------------------------------------------------------------------------------
 *
 * RT_Primitives
 * Box, Plane, Sphere
 *----------------------------------------------------------------------------------------------*/
typedef struct
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

	RT_BBox bbox;
} RT_Primitive;

typedef struct
{ 
	int v0, v1, v2;
	int normal;/*0 and 1(0 and 255)*/
	RT_Material material;
	RT_BBox bbox;
} RT_Triangle;

/*----------------------------------------------------------------------------------------------
 *
 * RT_Result
 * data of the results of the collisions
 *----------------------------------------------------------------------------------------------*/
typedef struct
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
 * Grid
 * 
 *----------------------------------------------------------------------------------------------*/
typedef struct
{
	RT_BBox bbox;
	int nx, ny, nz;
	int numTriangles;
	int numCells;
	/*transform*/
	RT_Mat4f invMatrix;
} RT_Grid;

/*----------------------------------------------------------------------------------------------
 *
 * RT_Light
 * data of the lights PointLight
 *----------------------------------------------------------------------------------------------*/
typedef struct
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
typedef struct
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
} RT_Camera;


typedef struct
{	
	/*data of the canvas*/
	RT_ViewPlane vp;

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
	seed random
	ulong seed;*/
} RT_DataScene;

/*----------------------------------------------------------------------------------------------
 *
 * Ray
 *
 *----------------------------------------------------------------------------------------------*/

 typedef struct
 {
	RT_Vec3f o;
	RT_Vec3f d;
 } RT_Ray;

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
 * Bounding Box
 * 
 *----------------------------------------------------------------------------------------------*/
bool BBox_Hit(const RT_BBox *bb, const RT_Ray *ray);
inline bool Inside(const RT_BBox *bb, const RT_Vec3f *p);

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
 * Method of collision verification with the Grid
 *
 *----------------------------------------------------------------------------------------------*/
 bool Grid_Hit(const RT_Grid *grid,
			   __constant RT_Primitive *objects,
			   __constant int *cells,
			   __constant int *count,
			   const RT_Ray *ray,
			   float *tmin,
			   RT_Result *r); 
 bool Grid_ShadowHit(const RT_Grid *grid,
					 __constant RT_Primitive *objects,
					 __constant int *cells,
					 __constant int *count, 
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
inline RT_Vec3f GetDirectionRayCam(const RT_Vec2f *point, __constant RT_Camera *camera);

/*----------------------------------------------------------------------------------------------
 *
 * Method for Ray
 *
 *----------------------------------------------------------------------------------------------*/
inline RT_Ray CreateRay(const RT_Vec3f o, const RT_Vec3f d);
inline RT_Vec3f HitPoint(const RT_Ray *r, const float t);

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
 * Method for super sampler
 *
 *----------------------------------------------------------------------------------------------*/
 RT_Point2f GenerateSamples();
 /*----------------------------------------------------------------------------------------------
 *
 * Method for the Tracer
 *
 *----------------------------------------------------------------------------------------------*/
RT_Vec3f TraceRay(__global const RT_Light *lights,
				  __constant RT_Primitive *objects,
				  __constant RT_DataScene *world, 
				  const RT_Ray *ray);