/*----------------------------------------------------------------------------------------------
 *
 * Camera
 *
 *----------------------------------------------------------------------------------------------*/
inline RT_Vec3f GetDirectionRayCam(const RT_Vec2f *point, 
								   __global const RT_Camera *camera)
{ 
	return normalize(camera->u * (*point).x +
					 camera->v * (*point).y +
					 camera->w * -camera->viewPlaneDistance);
}

/*----------------------------------------------------------------------------------------------
 *
 * Ray
 *
 *----------------------------------------------------------------------------------------------*/
/*
	Creates the ray
*/
inline RT_Ray CreateRay(const RT_Vec3f o, const RT_Vec3f d)
{
	RT_Ray r;
	r.o = o;
	r.d = d;
	return r;
}

/*
	The intersection point returns
*/
inline RT_Vec3f HitPoint(const RT_Ray *r, const float t)
{
	return (r->o + (r->d * t));
}

RT_Result Hit(__global const RT_Primitive *objects, 
			  const int numObj, const RT_Ray *ray)
{
	RT_Result r = CreateResult();
	RT_Vec3f normal;
	RT_Vec3f hp;

	float tmin = INFINITE;
	float t;

	for(int i = 0; i < numObj; i++)
	{
		RT_Primitive o = objects[i];
		if(Instance_Hit(&o, ray, &t, &r) && t < tmin)
		{ 
			r.hit = true;
			r.material = o.material;
			tmin = t;
			normal = r.normal;
			hp = r.lhitPoint;
		}
		/*switch(o.type)
		{ 
			case RT_BOX:
				if(Box_Hit(&o, ray, &t, &r) && t < tmin)
				{
					r.hit = true;
					r.material = o.material;
					tmin = t;
					normal = r.normal;
					hp = r.lhitPoint;
				}	
			break;
			case RT_PLANE:
				if(Plane_Hit(&o, ray, &t, &r) && t < tmin)
				{
					r.hit = true;
					r.material = o.material;
					tmin = t;
					normal = r.normal;
					hp = r.lhitPoint;
				}	
			break;
			case RT_SPHERE:
				if(Sphere_Hit(&o, ray, &t, &r) && t < tmin)
				{
					r.hit = true;
					r.material = o.material;
					tmin = t;
					normal = r.normal;
					hp = r.lhitPoint;
				}	
			break;

		}*/
	}
	if(r.hit)
	{ 
		r.t = tmin;
		r.normal = normal;
		r.lhitPoint = hp;
	}

	return r;
}

bool ShadowHit(__global const RT_Primitive *objects, 
			   const int numObj, const RT_Ray *ray, 
			   float tmin)
{
	float t;
	for(int i = 0; i < numObj; i++)
	{
		RT_Primitive o = objects[i];
		if(Instance_ShadowHit(&o, ray, &t) && t < tmin)
		{
			return true;
		}
		/*switch(o.type)
		{ 
			case RT_BOX:
				if(Box_ShadowHit(&o, ray, &t) && t < tmin)
				{
					return true;
				}	
			break;
			case RT_PLANE:
				if(Plane_ShadowHit(&o, ray, &t) && t < tmin)
				{
					return true;
				}	
			break;
			case RT_SPHERE:
				if(Sphere_ShadowHit(&o, ray, &t) && t < tmin)
				{
					return true;
				}	
			break;

		}*/
	}

	return false;
}

RT_Vec3f TraceRay(__global const RT_Light *lights,
				  __global const RT_Primitive *objects,
				  __global const RT_DataScene *world, 
				  const RT_Ray *ray)
{
	RT_Result r = Hit(objects, world->numObjects, ray);
	return r.hit? Shade(lights, objects, world, ray, &r) 
				: world->background;
}

