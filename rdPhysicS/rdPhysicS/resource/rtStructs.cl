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

typedef struct
{ 
	int color;
	float ls;
} RT_Emissive;

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

typedef struct
{ 
	RT_Vec3f p;
	RT_Vec3f a;
	RT_Vec3f b;
	RT_Vec3f normal;
	float r;
	RT_Emissive material;

	RT_TypeLamp type;

} RT_Lamp;

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
	RT_Emissive emissiveMaterial;
	int depth;
	char type;
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
	RT_Vec3f point;
	RT_Vec3f c_wi;
	float ls;
	float ex;
	int index;

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
	//RT_Vec3f lookAt;
	//RT_Vec3f up;

	float viewPlaneDistance;
	float zoom;

	//float rollAngle;
	//float exposureTime;

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

	/*data of the lights*/
	int numLamps;

	/*data of the objects*/
	int numObjects;

	/*data of the samples*/
	int numSamples;
	int numSets;
	/*int jump;
	ulong count;
	ulong numShuffledIndices;*/
	/*seed random*/
	uint seed;

	RT_TypeSampler type;
	RT_TypeTracer typeTracer;

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
			   __global const RT_Primitive *objects,
			   __global const RT_DataScene *world,
			   const RT_Ray *ray,
			   const RT_Result *r);

RT_Vec3f Emissive_Shade(const RT_Ray *ray,
					    const RT_Result *r);

inline RT_Vec3f Emissive_Color(const RT_Emissive *m);

/*----------------------------------------------------------------------------------------------
 *
 * it calculates the effects of the illumination in area in the material
 * 
 *----------------------------------------------------------------------------------------------*/
 RT_Vec3f AreaLight_Shade(__global const RT_Light *lights,
						  __global const RT_Lamp *lamps,
						  __global const RT_Primitive *objects,
						  __global const RT_DataScene *world,
						  const RT_Ray *ray,
						  const RT_Result *r,
						  const int sampleIndex,
						  uint *seed);


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
 * Methods to verify intercession with the lamp rectangular
 *
 *----------------------------------------------------------------------------------------------*/
bool Rect_Hit(const RT_Lamp *l, 
			  const RT_Ray *ray,
              float *tmin, RT_Result *r);

bool Rect_ShadowHit(const RT_Lamp *l, 
					const RT_Ray *ray,
					float *tmin);

/*----------------------------------------------------------------------------------------------
 *
 * Methods to verify intercession with the lamp disk
 *
 *----------------------------------------------------------------------------------------------*/
bool Disk_Hit(const RT_Lamp *l, 
			  const RT_Ray *ray,
              float *tmin, RT_Result *r);

bool Disk_ShadowHit(const RT_Lamp *l, 
					const RT_Ray *ray,
					float *tmin);

/*----------------------------------------------------------------------------------------------
 *
 * Method to verify intercession with the lamp
 *
 *----------------------------------------------------------------------------------------------*/
bool Lamp_Hit(const RT_Lamp *l, 
			  const RT_Ray *ray,
              float *tmin, RT_Result *r);

RT_Vec3f Lamp_Sample(__global const RT_DataScene *world,
					 const RT_Lamp *l,
					 const int index,
					 uint *seed);

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
			   __global const RT_Primitive *objects,
			   __constant int *cells,
			   __constant int *count,
			   const RT_Ray *ray,
			   float *tmin,
			   RT_Result *r); 
 bool Grid_ShadowHit(const RT_Grid *grid,
					 __global const RT_Primitive *objects,
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

inline RT_Vec3f Direction(__global const RT_DataScene *world,
						  RT_Light *l,
						  const RT_Lamp *o, 
						  const RT_Result *r,
						  const int index,
						  uint *seed);

inline RT_Vec3f Color(const RT_Light *l,
					  const RT_Lamp *o, 
					  const RT_Result *r);

bool InShadow(const RT_Light *l, 
			  __global const RT_Primitive *objects,
			  const int numObj, 
			  const RT_Ray *ray);

/*----------------------------------------------------------------------------------------------
 *
 * Methods for the AreaLight
 *
 *----------------------------------------------------------------------------------------------*/
 inline float G(const RT_Light *l,
				const RT_Lamp *o, 
				const RT_Result *r);

inline float PDF(const RT_Lamp *o);

/*----------------------------------------------------------------------------------------------
 *
 * The direction of the ray returns based on the camera
 *
 *----------------------------------------------------------------------------------------------*/
inline RT_Vec3f GetDirectionRayCam(const RT_Vec2f *point, __global const RT_Camera *camera);

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
RT_Result Hit(__global const RT_Lamp *lamps,
			  __global const RT_Primitive *objects, 
			  const int numLamps, const int numObj, 
			  const RT_Ray *ray);
bool ShadowHit(__global const RT_Primitive *objects, 
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
RT_Vec3f Raycasting_TraceRay(__global const RT_Light *lights,
							 __global const RT_Lamp *lamps,
							 __global const RT_Primitive *objects,
							 __global const RT_DataScene *world, 
							 const RT_Ray *ray);

RT_Vec3f AreaLighting_TraceRay(__global const RT_Light *lights,
							   __global const RT_Lamp *lamps,
							   __global const RT_Primitive *objects,
							   __global const RT_DataScene *world, 
							   const RT_Ray *ray,
							   const int sampleIndex,
							   uint *seed);

RT_Vec3f Tracer(__global const RT_Light *lights,
				__global const RT_Lamp *lamps,
				__global const RT_Primitive *objects,
				__global const RT_DataScene *world, 
				const RT_Ray *ray,
				const int sampleIndex,
				uint *seed);

uint RandIndex(uint *seed,
			   const int numSamples,
			   const int numSets);
/*----------------------------------------------------------------------------------------------
 *
 * Method for the generation of the Regular sampler
 *
 *----------------------------------------------------------------------------------------------*/
 RT_Vec2f RegularGenerateSampler(const int n,
							     const int id);

/*----------------------------------------------------------------------------------------------
 *
 * Method for the generation of the Jittered sampler
 *
 *----------------------------------------------------------------------------------------------*/
 RT_Vec2f JitteredGenerateSampler(uint *seed,
								  const int n,
							      const int id);

/*----------------------------------------------------------------------------------------------
 *
 * Method for the generation of the Hammersley sampler
 *
 *----------------------------------------------------------------------------------------------*/
 RT_Vec2f HammersleyGenerateSampler(const int numSamples,
							        const int id);

float Phi(int index);

/*----------------------------------------------------------------------------------------------
 *
 * Method for the generation of the NRooks sampler
 *
 *----------------------------------------------------------------------------------------------*/
 RT_Vec2f NRooksGenerateSampler(uint *seed,
								const int numSamples,
							    const int id);

/*----------------------------------------------------------------------------------------------
 *
 * Method for the generation of the MultiJittered sampler
 *
 *----------------------------------------------------------------------------------------------*/
 RT_Vec2f MultiJitteredGenerateSampler(uint *seed,
									   const int numSamples,
									   const int id);

void MapSampleToUnitDisk(RT_Vec2f *d);

