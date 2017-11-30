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

RT_Result Hit(__global const RT_Lamp *lamps,
			  __global const RT_Primitive *objects, 
			  const int numLamps, const int numObj, 
			  const RT_Ray *ray)
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
			r.type = 0;
			r.material = o.material;
			tmin = t;
			normal = r.normal;
			hp = r.lhitPoint;
		}
	}

	for(int i = 0; i < numLamps; i++)
	{ 
		RT_Lamp l = lamps[i];
		if(Lamp_Hit(&l, ray, &t, &r))
		{ 
			r.hit = true;
			r.type = 1;
			r.emissiveMaterial = l.material;
			tmin = t;
			normal = l.normal;
			hp = r.lhitPoint;
		}
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
	}

	return false;
}

RT_Vec3f Raycasting_TraceRay(__global const RT_Light *lights,
							 __global const RT_Lamp *lamps,
							 __global const RT_Primitive *objects,
							 __global const RT_DataScene *world, 
							 const RT_Ray *ray)
{
	RT_Result r = Hit(lamps, objects, world->numLamps, world->numObjects, ray);

	if(r.hit)
	{ 
		return (r.type == 0)? Shade(lights, objects, world, ray, &r)
							: Emissive_Shade(ray, &r);
	}

	return world->background;
}

RT_Vec3f AreaLighting_TraceRay(__global const RT_Light *lights,
							   __global const RT_Lamp *lamps,
							   __global const RT_Primitive *objects,
							   __global const RT_DataScene *world, 
							   const RT_Ray *ray,
							   const int sampleIndex,
							   uint *seed)
{ 
	RT_Result r = Hit(lamps, objects, world->numLamps, world->numObjects, ray);

	if(r.hit)
	{ 
		return (r.type == 0)? AreaLight_Shade(lights, lamps, objects, world,
											  ray, &r, sampleIndex, seed)
							: Emissive_Shade(ray, &r);
	}

	return world->background;
}

RT_Vec3f Tracer(__global const RT_Light *lights,
				__global const RT_Lamp *lamps,
				__global const RT_Primitive *objects,
				__global const RT_DataScene *world, 
				const RT_Ray *ray,
				const int sampleIndex,
				uint *seed)
{ 
	switch(world->typeTracer)
	{ 
	case RT_AREA_LIGHTING:
		return AreaLighting_TraceRay(lights, lamps, objects, 
									 world, ray, sampleIndex, seed);
	case RT_RAYCASTING:
		return Raycasting_TraceRay(lights, lamps, objects, world, ray);
	}
}