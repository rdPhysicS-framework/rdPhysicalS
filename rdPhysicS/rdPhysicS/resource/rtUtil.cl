#pragma OPENCL EXTENSION cl_khr_fp64 : enable

#define ANGLE 180.0f

#define PI 3.14159265358979f
#define PI2 (PI * 2)
#define INVPI 1 / PI

#define RANDMAX 0x7FFF
#define RAND_MASK 4294883355L
#define INFINITE 10000000.0f

#define MULTIPLIER 0x5DEECE66DL
#define ADDEND 0xBL
#define MASK (1L << 48) - 1

#define EPSILON 0.01f

#define COLORMAX 0xFF
#define RMASK 0x000000FF
#define GMASK 0x0000FF00
#define BMASK 0x00FF0000
#define AMASK 0xFF000000

#define RSHIFT 0
#define GSHIFT 8
#define BSHIFT 16
#define ASHIFT 24

#define SIZE_MATRIX 4

#define TO_DEG (ANGLE/PI)
#define TO_RAD  (PI/ANGLE)

typedef enum
{ 
	RT_BOX,
	RT_PLANE,
	RT_SPHERE
} RT_TypeObject;

typedef enum
{ 
	RT_PHONG_MATERIAL,
	RT_REFLECTIVE_MATERIAL,
	RT_SIMPLE_MATERIAL
} RT_TypeMaterial;

typedef enum
{ 
	RT_AMBIENT_LIGHT,
	RT_AMBIENT_OCCLUDER_LIGHT,
	RT_AREA_LIGHT,
	RT_POINT_LIGHT
} RT_TypeLight;

typedef enum
{ 
	RT_GLOSSY_SPECULAR,
	RT_LAMBERTIAN,
	RT_PERFECT_SPECULAR
} RT_TypeBRDF;

typedef enum
{ 
	RT_FRESNEL_TRANSMITTER,
	RT_PERFECT_TRANSMITTER
} RT_TypeBTDF;

typedef enum
{ 
	RT_HAMMERSLEY,
	RT_JITTERED,
	RT_REGULAR
} RT_TypeSampler;

typedef enum
{ 
	RT_CIRCULAR,
	RT_RECTANGULAR,
	RT_SPHERICAL
} RT_TypeLamp;

typedef enum
{ 
	RT_AREA_LIGHTING,
	RT_RAYCASTING
} RT_TypeTracer;

inline float toRadians(const float d)
{
	return (float)(d * TO_RAD);
}

inline float toDegrees(const float r)
{
	return (float)(r * TO_DEG);
}

inline float _absf(float x)
{ 
	return (x < 0)? (x * -1) : x;
}

int next(uint *seed, int bits)
{
	*seed = (*seed * MULTIPLIER + ADDEND) & MASK;
	return (int)(*seed >> (48 - bits));
}

int nextInt(uint *seed, int bound)
{
	int r = next(seed, 31);
	int m = bound == 0? 0 : bound - 1;

	if ((bound & m) == 0)
	{
		r = (int)((bound * (uint)r) >> 31);
	}
	else
	{
		for (int i = r; 
			 i - (r = i % bound) + m < 0;
			  i = next(seed, 31)){ }
	}

	return r;
}

inline int randInt(uint *seed)
{ 
	return nextInt(seed, RANDMAX);
}

inline float randFloat(uint *seed)
{ 
	return (float)randInt(seed) / RANDMAX;
}

inline float randFloat2(uint *seed, float l, float h)
{ 
	return randFloat(seed) * (h - l) + l;
}

inline int randInt2(uint *seed, int l, int h)
{ 
	return (int)randFloat2(seed, l, h);
}

/*----------------------------------------------------------------------------------------------
 *
 * Math
 *
 *----------------------------------------------------------------------------------------------*/
typedef float2 RT_Vec2f;
typedef float3 RT_Vec3f;
typedef float4 RT_Vec4f;

typedef union
{ 
	struct{ float x; float y; };
	float s[2];
} RT_Point2f;

typedef struct
{
	float m[4][4];
} RT_Mat4f;

/*----------------------------------------------------------------------------------------------
 *
 *Methods of matrix 4f*
 *
 *----------------------------------------------------------------------------------------------*/

inline RT_Mat4f create(float a, float b, float c, float d,
					    float e, float f, float g, float h,
					    float k, float l, float m, float n,
					    float o, float p, float q, float r)
{
	RT_Mat4f mt;
	mt.m[0][0] = a; mt.m[0][1] = b; mt.m[0][2] = c; mt.m[0][3] = d;
	mt.m[1][0] = e; mt.m[1][1] = f; mt.m[1][2] = g; mt.m[1][3] = h;
	mt.m[2][0] = k; mt.m[2][1] = l; mt.m[2][2] = m; mt.m[2][3] = n;
	mt.m[3][0] = o; mt.m[3][1] = p; mt.m[3][2] = q; mt.m[3][3] = r;
	return mt;
}

inline RT_Mat4f identity()
{
	return create(1, 0, 0, 0,
				  0, 1, 0, 0,
				  0, 0, 1, 0,
				  0, 0, 0, 1 );
}

inline RT_Mat4f null()
{
	return create(0, 0, 0, 0,
				  0, 0, 0, 0,
				  0, 0, 0, 0,
				  0, 0, 0, 0 );
}

inline RT_Mat4f copy(const RT_Mat4f *a)
{
	RT_Mat4f r;
	for(int i = 0; i < SIZE_MATRIX; i++)
	{ 
		for(int j = 0; j < SIZE_MATRIX; j++)
		{
			r.m[i][j] = a->m[i][j];
		}
	}

	return r;
}

inline RT_Mat4f transpose(const RT_Mat4f *m)
{
	RT_Mat4f mt;
	mt.m[0][0] = m->m[0][0]; mt.m[0][1] = m->m[1][0]; mt.m[0][2] = m->m[2][0]; mt.m[0][3] = m->m[3][0];
	mt.m[1][0] = m->m[0][1]; mt.m[1][1] = m->m[1][1]; mt.m[1][2] = m->m[2][1]; mt.m[1][3] = m->m[3][1];
	mt.m[2][0] = m->m[0][2]; mt.m[2][1] = m->m[1][2]; mt.m[2][2] = m->m[2][2]; mt.m[2][3] = m->m[3][2];
	mt.m[3][0] = m->m[0][3]; mt.m[3][1] = m->m[1][3]; mt.m[3][2] = m->m[2][3]; mt.m[3][3] = m->m[3][3];
	return mt;
}

inline float determinant(const RT_Mat4f *m)
{
	return m->m[0][0] * (m->m[1][1] * (m->m[2][2] * m->m[3][3] - m->m[2][3]   * m->m[3][2]) +
           m->m[1][2] * (m->m[2][3] *  m->m[3][1] - m->m[2][1] * m->m[3][3])  +
           m->m[1][3] * (m->m[2][1] *  m->m[3][2] - m->m[2][2] * m->m[3][1])) -

           m->m[0][1] * (m->m[1][0] * (m->m[2][2] * m->m[3][3] - m->m[2][3]   * m->m[3][2]) +
           m->m[1][2] * (m->m[2][3] *  m->m[3][0] - m->m[2][0] * m->m[3][3])  +
           m->m[1][3] * (m->m[2][0] *  m->m[3][2] - m->m[2][2] * m->m[3][0])) +
		   
           m->m[0][2] * (m->m[1][0] * (m->m[2][1] * m->m[3][3] - m->m[2][3]   * m->m[3][1]) +
           m->m[1][1] * (m->m[2][3] *  m->m[3][0] - m->m[2][0] * m->m[3][3])  +
           m->m[1][3] * (m->m[2][0] *  m->m[3][1] - m->m[2][1] * m->m[3][0])) -
		   
           m->m[0][3] * (m->m[1][0] * (m->m[2][1] * m->m[3][2] - m->m[2][2]   * m->m[3][1]) +
           m->m[1][1] * (m->m[2][2] *  m->m[3][0] - m->m[2][0] * m->m[3][2])  +
           m->m[1][2] * (m->m[2][0] *  m->m[3][1] - m->m[2][1] * m->m[3][0]));
}

inline RT_Mat4f inverse(const RT_Mat4f *m)
{
	//RT_Mat4f inv;

	float a = m->m[0][0] * m->m[1][1] - m->m[0][1] * m->m[1][0];
	float b = m->m[0][0] * m->m[1][2] - m->m[0][2] * m->m[1][0];
	float c = m->m[0][0] * m->m[1][3] - m->m[0][3] * m->m[1][0];
	float d = m->m[0][1] * m->m[1][2] - m->m[0][2] * m->m[1][1];
	float e = m->m[0][1] * m->m[1][3] - m->m[0][3] * m->m[1][1];
	float f = m->m[0][2] * m->m[1][3] - m->m[0][3] * m->m[1][2];
	float g = m->m[2][0] * m->m[3][1] - m->m[2][1] * m->m[3][0];
	float h = m->m[2][0] * m->m[3][2] - m->m[2][2] * m->m[3][0];
	float i = m->m[2][0] * m->m[3][3] - m->m[2][3] * m->m[3][0];
	float j = m->m[2][1] * m->m[3][2] - m->m[2][2] * m->m[3][1];
	float k = m->m[2][1] * m->m[3][3] - m->m[2][3] * m->m[3][1];
	float l = m->m[2][2] * m->m[3][3] - m->m[2][3] * m->m[3][2];
	float det = a * l - b * k + c * j + d * i - e * h + f * g;
	det = 1.0f / det;

	return create( (m->m[1][1] * l - m->m[1][2] * k + m->m[1][3] * j) * det,
				  (-m->m[0][1] * l + m->m[0][2] * k - m->m[0][3] * j) * det,
				   (m->m[3][1] * f - m->m[3][2] * e + m->m[3][3] * d) * det,
				  (-m->m[2][1] * f + m->m[2][2] * e - m->m[2][3] * d) * det,
				  (-m->m[1][0] * l + m->m[1][2] * i - m->m[1][3] * h) * det,
				   (m->m[0][0] * l - m->m[0][2] * i + m->m[0][3] * h) * det,
				  (-m->m[3][0] * f + m->m[3][2] * c - m->m[3][3] * b) * det,
				   (m->m[2][0] * f - m->m[2][2] * c + m->m[2][3] * b) * det,
				   (m->m[1][0] * k - m->m[1][1] * i + m->m[1][3] * g) * det,
				  (-m->m[0][0] * k + m->m[0][1] * i - m->m[0][3] * g) * det,
				   (m->m[3][0] * e - m->m[3][1] * c + m->m[3][3] * a) * det,
				  (-m->m[2][0] * e + m->m[2][1] * c - m->m[2][3] * a) * det,
				  (-m->m[1][0] * j + m->m[1][1] * h - m->m[1][2] * g) * det,
				   (m->m[0][0] * j - m->m[0][1] * h + m->m[0][2] * g) * det,
				  (-m->m[3][0] * d + m->m[3][1] * b - m->m[3][2] * a) * det,
				   (m->m[2][0] * d - m->m[2][1] * b + m->m[2][2] * a) * det);
}

inline RT_Mat4f affTranslation(const RT_Vec3f *v)
{
	return create(1, 0, 0, (*v).x,
				  0, 1, 0, (*v).y,
				  0, 0, 1, (*v).z,
				  0, 0, 0, 1    );
}

inline RT_Mat4f affTranslationF(const float x, const float y, const float z)
{
	return create(1, 0, 0, x,
				  0, 1, 0, y,
				  0, 0, 1, z,
				  0, 0, 0, 1 );
}

inline RT_Mat4f affRotationX(const float a)
{
	float c = cos(a);
	float s = sin(a);

	return create(1, 0,  0, 0,
					 0, c, -s, 0,
					 0, s,  c, 0,
					 0, 0,  0, 1 );
}

inline RT_Mat4f affRotationY(const float a)
{
	float c = cos(a);
	float s = sin(a);

	return create( c, 0, s, 0,
					  0, 1, 0, 0,
					 -s, 0, c, 0,
					  0, 0, 0, 1 );
}

inline RT_Mat4f affRotationZ(const float a)
{
	float c = cos(a);
	float s = sin(a);
	
	return create(c, -s, 0, 0,
					 s,  c, 0, 0,
					 0,  0, 1, 0,
					 0,  0, 0, 1 );
}

inline RT_Mat4f affScaling(const float s)
{
	return create(s, 0, 0, 0,
					 0, s, 0, 0,
					 0, 0, s, 0,
					 0, 0, 0, 1 );
}

inline RT_Mat4f affScalingF(const float x, const float y, const float z)
{
	return create(x, 0, 0, 0,
				  0, y, 0, 0,
				  0, 0, z, 0,
				  0, 0, 0, 1 );
}

inline RT_Mat4f affScalingV(const RT_Vec3f *v)
{
	return affScalingF((*v).x, (*v).y, (*v).z);
}

inline RT_Mat4f affInvTranslation(const RT_Vec3f *v)
{
	return affTranslationF(-(*v).x, -(*v).y, -(*v).z);
}

inline RT_Mat4f affInvTranslationF(const float x, const float y, const float z)
{
	return affTranslationF(-x, -y, -z);
}

inline RT_Mat4f affInvRotationX(const float a)
{
	float c = cos(a);
	float s = sin(a);

	return create(1,  0, 0, 0,
				  0,  c, s, 0,
				  0, -s, c, 0,
				  0,  0, 0, 1 );
}

inline RT_Mat4f affInvRotationY(const float a)
{
	float c = cos(a);
	float s = sin(a);

	return create( c, 0, -s, 0,
				   0, 1,  0, 0,
				   s, 0,  c, 0,
				   0, 0,  0, 1 );
}

inline RT_Mat4f affInvRotationZ(const float a)
{
	float c = cos(a);
	float s = sin(a);
	
	return create( c, s, 0, 0,
				  -s,  c, 0, 0,
				   0,  0, 1, 0,
				   0,  0, 0, 1 );
}

inline RT_Mat4f affInvScaling(const float s)
{
	return affScaling(1.0f/s);
}

inline RT_Mat4f affInvScalingV(const RT_Vec3f *v)
{
	return affScalingF(1.0f/(*v).x, 1.0f/(*v).y, 1.0f/(*v).z);
}


inline RT_Mat4f affInvScalingF(const float x, const float y, const float z)
{
	return affScalingF(1.0f/x, 1.0f/y, 1.0f/z);
}


inline RT_Mat4f add(const RT_Mat4f *a, const RT_Mat4f *b)
{
	RT_Mat4f r;
	for(int i = 0; i < SIZE_MATRIX; i++)
	{
		for(int j = 0; j < SIZE_MATRIX; j++)
		{
			r.m[i][j] = a->m[i][j] + b->m[i][j];
		}
	}

	return r;
}

inline RT_Mat4f addS(const RT_Mat4f *a, const float s)
{
	RT_Mat4f r;
	for(int i = 0; i < SIZE_MATRIX; i++)
	{
		for(int j = 0; j < SIZE_MATRIX; j++)
		{
			r.m[i][j] = a->m[i][j] + s;
		}
	}

	return r;
}

inline RT_Mat4f sub(const RT_Mat4f *a, const RT_Mat4f *b)
{
	RT_Mat4f r;
	for(int i = 0; i < SIZE_MATRIX; i++)
	{
		for(int j = 0; j < SIZE_MATRIX; j++)
		{
			r.m[i][j] = a->m[i][j] - b->m[i][j];
		}
	}

	return r;
}

inline RT_Mat4f subS(const RT_Mat4f *a, const float s)
{
	RT_Mat4f r;
	for(int i = 0; i < SIZE_MATRIX; i++)
	{
		for(int j = 0; j < SIZE_MATRIX; j++)
		{
			r.m[i][j] = a->m[i][j] - s;
		}
	}

	return r;
}

inline RT_Mat4f mul(const RT_Mat4f *a, const RT_Mat4f *b)
{
	RT_Mat4f r = null();

	for(int c = 0; c < SIZE_MATRIX; c++)
	{ 
		for(int i = 0; i < SIZE_MATRIX; i++)
		{
			for(int j = 0; j < SIZE_MATRIX; j++)
			{
				r.m[c][i] += a->m[c][j] * b->m[j][i];
			}
		}
	}

	return r;
}

inline RT_Mat4f mulS(const RT_Mat4f *a, const float s)
{
	RT_Mat4f r;
	for(int i = 0; i < SIZE_MATRIX; i++)
	{
		for(int j = 0; j < SIZE_MATRIX; j++)
		{ 
			r.m[i][j] = a->m[i][j] * s;
		}
	}

	return r;
}

inline RT_Mat4f div(const RT_Mat4f *a, const float s)
{
	RT_Mat4f r;
	for(int i = 0; i < SIZE_MATRIX; i++)
	{ 
		for(int j = 0; j < SIZE_MATRIX; j++)
		{ 
			r.m[i][j] = a->m[i][j] / s;
		}
	}
	return r;
}

/*----------------------------------------------------------------------------------------------
 *
 * Transform Vector
 *
 *----------------------------------------------------------------------------------------------*/

inline RT_Vec3f TransformPoint(const RT_Mat4f *m, const RT_Vec3f *p)
{
	return (RT_Vec3f)(m->m[0][0] * (*p).x + m->m[0][1] * (*p).y + m->m[0][2] * (*p).z + m->m[0][3],
					  m->m[1][0] * (*p).x + m->m[1][1] * (*p).y + m->m[1][2] * (*p).z + m->m[1][3],
					  m->m[2][0] * (*p).x + m->m[2][1] * (*p).y + m->m[2][2] * (*p).z + m->m[2][3] );
}

inline RT_Vec3f TransformDirection(const RT_Mat4f *m, const RT_Vec3f *d)
{
	return (RT_Vec3f)(m->m[0][0] * (*d).x + m->m[0][1] * (*d).y + m->m[0][2] * (*d).z,
					  m->m[1][0] * (*d).x + m->m[1][1] * (*d).y + m->m[1][2] * (*d).z,
					  m->m[2][0] * (*d).x + m->m[2][1] * (*d).y + m->m[2][2] * (*d).z );
}

inline RT_Vec3f TransformNormal(const RT_Mat4f *m, const RT_Vec3f *n)
{
	RT_Vec3f r = (RT_Vec3f)(m->m[0][0] * (*n).x + m->m[1][0] * (*n).y + m->m[2][0] * (*n).z,
						    m->m[0][1] * (*n).x + m->m[1][1] * (*n).y + m->m[2][1] * (*n).z,
						    m->m[0][2] * (*n).x + m->m[1][2] * (*n).y + m->m[2][2] * (*n).z );
	return normalize(r);
				   
}

inline RT_Vec3f reflect(const RT_Vec3f *v, const RT_Vec3f *n)
{
	float d = dot(*v, *n);

	return (RT_Vec3f)((*v).x - 2.0f * d * (*n).x,
					  (*v).y - 2.0f * d * (*n).y,
					  (*v).z - 2.0f * d * (*n).z );
}

inline RT_Vec3f refract(const RT_Vec3f *v, const RT_Vec3f *n, const float i)
{
	float d = dot(*v, *n);
	float k = 1.0f - pow(i, 2) * (1.0f - pow(d, 2));

	if(k < 0.0f)
	{
		return *v;
	}

	float sr = sqrt(k);

	return (RT_Vec3f)(i * (*v).x - (*n).x * (i * d + sr),
					  i * (*v).y - (*n).y * (i * d + sr),
					  i * (*v).z - (*n).z * (i * d + sr) );
}

inline RT_Vec3f lerp(const RT_Vec3f *a, const RT_Vec3f *b, const float t)
{
	return (RT_Vec3f)((*a).x + ((*b).x - (*a).x) * t,
					  (*a).y + ((*b).y - (*a).y) * t,
					  (*a).z + ((*b).z - (*a).z) * t );
}

inline void swap(__global RT_Vec3f *a, const RT_Vec3f *b)
{
	(*a).x = (*b).x;
	(*a).y = (*b).y;
	(*a).z = (*b).z;
}

inline RT_Vec3f _clamp(const RT_Vec3f *v, const float minimum, const float maximum)
{
	return (RT_Vec3f)(((*v).x < minimum)? minimum : ((*v).x > maximum)? maximum : (*v).x,
					  ((*v).y < minimum)? minimum : ((*v).y > maximum)? maximum : (*v).y,
					  ((*v).z < minimum)? minimum : ((*v).z > maximum)? maximum : (*v).z );	
}

inline void Saturate(RT_Vec3f *c)
{ 
	*c = _clamp(c, 0, 1);
}

inline float sizeSqr(const RT_Vec3f v)
{ 
	return ((v.x * v.x) + 
			(v.y * v.y) + 
			(v.z * v.z)  );
}

/*----------------------------------------------------------------------------------------------
 *
 * Color
 *
 *----------------------------------------------------------------------------------------------*/

 typedef struct
 {
	//float rf, gf, bf, af;
	int r, g, b, a;
	int rgba;

 } RT_Color;

 inline RT_Color CreatePixelColor(int r, int g, int b, int a)
 {
	RT_Color c;
	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;

	/*c.rf = r/255.f;
	c.gf = g/255.f;
	c.bf = b/255.f;
	c.af = a/255.f;*/

	c.rgba = (((r & 0xFF) << RSHIFT) |
			  ((g & 0xFF) << GSHIFT) |
			  ((b & 0xFF) << BSHIFT) |
			  ((a & 0xFF) << ASHIFT)  );

	return c;
 }

 inline RT_Color CreatePixelColorf(float r, float g, float b, float a)
 {
	return CreatePixelColor(r*255, g*255, b*255, a*255);
 }

 inline RT_Color CreatePixelColorv4(const RT_Vec4f c)
 {
	return CreatePixelColor(c.x*255, c.y*255, c.z*255, c.w*255);
 }

 inline RT_Color CreatePixelColorv3(const RT_Vec3f c)
 {
	return CreatePixelColor(c.x*255, c.y*255, c.z*255, 255);
 }

 inline RT_Color CreatePixelColor32(const int rgba)
 {
	RT_Color c;
	c.r = (rgba & RMASK) >> RSHIFT;
	c.g = (rgba & GMASK) >> GSHIFT;
	c.b = (rgba & BMASK) >> BSHIFT;
	c.a = (rgba & AMASK) >> ASHIFT;

	c.rgba = rgba;

	return c;
 }


