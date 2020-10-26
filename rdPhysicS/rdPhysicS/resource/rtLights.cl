/*----------------------------------------------------------------------------------------------
 *
 * Methods of the PointLight
 *
 *----------------------------------------------------------------------------------------------*/
 RT_Light Create_PointLight(const RT_Vec3f p, const RT_Vec3f c, const float ls)
 {
	RT_Light l;
	l.point = p;
	l.c_wi = c;
	l.ls = ls;
	return l;
 }

inline void computeUVW(RT_Vec3f *u, RT_Vec3f *v, 
					   RT_Vec3f *w, const RT_Result *r)
{ 
	*w = normalize(r->normal);
	*v = normalize(cross(*w, (RT_Vec3f)(0.0072f, 1.0f, 0.0034f)));
	*u = cross(*v, *w);
}

inline RT_Vec2f AmbientOcclusionSample(__global const RT_DataScene *world,
									   const int index,
									   uint *seed)
{ 
	switch(world->type)
	{ 
		case RT_HAMMERSLEY:
		break;
		case RT_JITTERED:
			return JitteredGenerateSampler(seed, sqrt((float)world->numSamples), index);
		case RT_REGULAR:
			return RegularGenerateSampler(sqrt((float)world->numSamples), index);
	}

	return (RT_Vec2f)(0.0f);
}

inline RT_Vec3f Direction(__global const RT_DataScene *world,
						  RT_Light *l,
						  const RT_Lamp *o, 
						  const RT_Result *r,
						  const int index,
						  uint *seed)
{
	switch(l->type)
	{ 
		case RT_AMBIENT_LIGHT:
		{ 
			return (RT_Vec3f)(0.0f);
		}
		case RT_AMBIENT_OCCLUDER_LIGHT:
		{ 
			RT_Vec3f u, v, w;
			computeUVW(&u, &v, &w, r);

			RT_Vec2f s = AmbientOcclusionSample(world, index, seed);

			RT_Vec3f sp = MapSampleToHemisphere(&s, 1);

			return (sp.x * u + sp.y * v + sp.z * w);
		}
		case RT_AREA_LIGHT:
		{
			l->point = Lamp_Sample(world, o, index, seed);
			l->c_wi = normalize(l->point - r->lhitPoint);
			return l->c_wi;
		}
		case RT_POINT_LIGHT:
		{
			if(o->type == RT_SPHERICAL)
			{ 
				RT_Vec3f dir;
				//RT_Vec3f dir = Lamp_Sample(world, o, index, seed);
				dir.x = l->point.x + 1.0f * (2.0f * randFloat(seed) - 1.0f);
				dir.y = l->point.y + 1.0f * (2.0f * randFloat(seed) - 1.0f);
				dir.z = l->point.z + 1.0f * (2.0f * randFloat(seed) - 1.0f);
				return normalize(dir - r->lhitPoint);
			}
			return normalize(l->point - r->lhitPoint);
		}
	}
	return (RT_Vec3f)(0.0f);
}

inline RT_Vec3f Color(const RT_Light *l, 
					  const RT_Lamp *o,
					  __global const RT_Primitive *objects,
					  __global const RT_DataScene *world,
					  const RT_Result *r,
					  const int index,
					  uint *seed)
{
	switch(l->type)
	{ 
		case RT_AMBIENT_LIGHT:
		{ 
			return (l->c_wi * l->ls);
		}
		case RT_AMBIENT_OCCLUDER_LIGHT:
		{ 
			RT_Ray _ray = CreateRay(r->lhitPoint, Direction(world,
												  l, o, r, index, seed)); 

			return InShadow(l, objects, 0, &_ray)? 
				   (l->c_wi * (l->ls * l->ex)) :
				   (l->c_wi * l->ls);
		}
		case RT_AREA_LIGHT:
		{ 
			return (dot(-o->normal, l->c_wi) > 0.0f) ?
						Emissive_Color(&o->material) :
						(RT_Vec3f)(0.0f);

		}
		case RT_POINT_LIGHT:
		{
			float dist = length(r->lhitPoint - l->point);
			return l->c_wi * (l->ls / pow(dist, l->ex));
		}
	}

	return (RT_Vec3f)(0.0f);
}


bool InShadow(const RT_Light *l, 
			  __global const RT_Primitive *objects,
			  const int numObj, 
			  const RT_Ray *ray)
{	
	float tmin;
	switch(l->type)
	{ 
		case RT_AMBIENT_LIGHT:
		{}
		break;
		case RT_AMBIENT_OCCLUDER_LIGHT:
		{}
		break;
		case RT_AREA_LIGHT:
		{
			tmin = dot(l->point - ray->o, ray->d);
		}
		break;
		case RT_POINT_LIGHT:
		{ 
			tmin = length(l->point - ray->o);
		}
		break;
	}

	return ShadowHit(objects, numObj, ray, tmin); 
}


/*----------------------------------------------------------------------------------------------
 *
 * Methods for the AreaLight
 *
 *----------------------------------------------------------------------------------------------*/
 inline float G(const RT_Light *l,
				const RT_Lamp *o, 
				const RT_Result *r)
{ 
	float _dot = dot(-o->normal, l->c_wi);
	float d = sizeSqr(l->point - r->lhitPoint);
	return (_dot / d);
}

inline float PDF(const RT_Lamp *o)
{ 
	if(o->type == RT_CIRCULAR)
		return 1.0f / (PI * o->r * o->r);
	else if(o->type == RT_RECTANGULAR)
		return (1.0f / o->r);//(length(o->a) * length(o->b)));
	else if(o->type == RT_SPHERICAL)
		return (1.0f / (4.0f * PI * o->r * o->r));
	
	return 0.0f;
}
