#include "Objects.h"
#include "..\..\Util\LogError.h"

USING_RDPS
USING_PKG
//------------------------------------------------------------------------------------------------------------->
RT_BRDF::RT_BRDF()
{}

RT_BRDF::RT_BRDF(const RT::Vec4f &_color,
				 const float _k, 
				 const float _ex, 
				 const RT_TypeBRDF _type) :
		 color(_color),
		 k(_k),
		 exp(_ex),
		 type(_type)
{}

RT_BRDF &RT_BRDF::operator=(const RT_BRDF &other)
{
	if(type != other.type)
		Logger::Log("ERROR: type of the BRDF is different.");

	color = other.color;
	k = other.k;
	exp = other.exp;
	return (*this);
}

//------------------------------------------------------------------------------------------------------------->
RT_Material::RT_Material()
{
}

RT_Material::RT_Material(const RT_BRDF &_ambient,
						 const RT_BRDF &_diffuse, 
						 const RT_BRDF &_specular, 
						 const RT_BRDF &_refl) :
			 ambient(_ambient),
			 diffuse(_diffuse),
			 specular(_specular),
			 refl(_refl)
{}

RT_Material &RT_Material::operator=(const RT_Material &other)
{
	ambient  = other.ambient;
	diffuse  = other.diffuse;
	specular = other.specular;
	refl     = other.refl;
	return (*this);
}

//------------------------------------------------------------------------------------------------------------->
RT_BBox::RT_BBox()
{}

RT_BBox::RT_BBox(const float _x0, 
				 const float _y0, 
				 const float _z0, 
				 const float _x1, 
				 const float _y1, 
				 const float _z1) :
		 x0(_x0), y0(_y0), z0(_z0),
		 x1(_x1), y1(_y1), z1(_z1)
{}

RT_BBox &RT_BBox::operator=(const RT_BBox &other)
{
	x0 = other.x0;
	y0 = other.y0;
	z0 = other.z0;

	x1 = other.x1;
	y1 = other.y1;
	z1 = other.z1;

	return (*this);
}

//------------------------------------------------------------------------------------------------------------->
RT_Primitive::RT_Primitive()
{}

RT_Primitive::RT_Primitive(const RT::Vec4f &_p,
						   const RT::Vec4f &_s,
						   const float _r, 
						   const RT_Material &_material, 
						   const RT_TypeObject _type, 
						   const RT::Mat4f &_invMatrix, 
						   const RT_BBox &_bbox) :
			  p(_p),
			  s(_s),
			  r(_r),
			  material(_material),
			  type(_type),
			  invMatrix(_invMatrix),
			  bbox(_bbox)
{}

RT_Primitive &RT_Primitive::operator=(const RT_Primitive &other)
{
	if (type != other.type)
		Logger::Log("ERROR: type of the primitive is different.");

	p = other.p;
	s = other.s;
	r = other.r;
	material = other.material;
	invMatrix = other.invMatrix;
	bbox = other.bbox;
	return (*this);
}

//------------------------------------------------------------------------------------------------------------->
RT_Light::RT_Light()
{}

RT_Light::RT_Light(const RT::Vec4f &_position,
				   const RT::Vec4f &_color,
				   const float _ls, 
				   const float _ex) :
		  position(_position),
		  color(_color),
		  ls(_ls),
		  ex(_ex)
{}

RT_Light &RT_Light::operator=(const RT_Light &other)
{
	if (type != other.type)
		Logger::Log("ERROR: type of the light is different.");

	position = other.position;
	color = other.color;
	ls = other.ls;
	ex = other.ex;
	return (*this);
}

//------------------------------------------------------------------------------------------------------------->
RT_ViewPlane::RT_ViewPlane()
{}

RT_ViewPlane::RT_ViewPlane(const int _width, 
						   const int _height, 
						   const RT::Vec4f &_sp) :
			  width(_width),
			  height(_height),
			  sp(_sp)
{}

RT_ViewPlane &RT_ViewPlane::operator=(const RT_ViewPlane &other)
{
	width = other.width;
	height = other.height;
	sp = other.sp;
	return (*this);
}

//------------------------------------------------------------------------------------------------------------->
RT_Camera::RT_Camera()
{}

RT_Camera::RT_Camera(const RT::Vec4f &_eye,
					 const RT::Vec4f &_lookAt,
					 const RT::Vec4f &_up,
					 const float _viewPlaneDistance, 
					 const float _zoom, 
					 const float _rollAngle, 
					 const float _exposureTime, 
					 const RT::Vec4f &_u,
					 const RT::Vec4f &_v,
					 const RT::Vec4f &_w) :
			eye(_eye),
			lookAt(_lookAt),
			up(_up),
			viewPlaneDistance(_viewPlaneDistance),
			zoom(_zoom),
			rollAngle(_rollAngle),
			exposureTime(_exposureTime),
			u(_u), v(_v), w(_w)
{}

RT_Camera &RT_Camera::operator=(const RT_Camera &other)
{
	eye = other.eye;
	lookAt = other.lookAt;
	up = other.up;
	viewPlaneDistance = other.viewPlaneDistance;
	zoom = other.zoom;
	rollAngle = other.rollAngle;
	exposureTime = other.exposureTime;
	u = other.u;
	v = other.v;
	w = other.w;
	return (*this);
}

//------------------------------------------------------------------------------------------------------------->
RT_DataScene::RT_DataScene()
{
}

RT_DataScene::RT_DataScene(const RT_ViewPlane &_vp, 
						   const RT::Vec4f &_background,
						   const int _numLights, 
						   const int _numObjects) :
			  vp(_vp),
			  background(_background),
			  numLights(_numLights),
			  numObjects(_numObjects)
{}

RT_DataScene &RT_DataScene::operator=(const RT_DataScene &other)
{
	vp = other.vp;
	background = other.background;
	numLights = other.numLights;
	numObjects = other.numObjects;
}
