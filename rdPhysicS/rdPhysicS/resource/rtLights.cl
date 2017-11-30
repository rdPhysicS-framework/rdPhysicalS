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
		case RT_AREA_LIGHT:
		{
			l->point = Lamp_Sample(world, o, index, seed);
			l->c_wi = normalize(l->point - r->lhitPoint);
			return l->c_wi;
		}
		case RT_POINT_LIGHT:
		{
			return normalize(l->point - r->lhitPoint);
		}
	}
	return (RT_Vec3f)(0.0f);
}

inline RT_Vec3f Color(const RT_Light *l, 
					  const RT_Lamp *o,
					  const RT_Result *r)
{
	//RT_Vec3f c = (RT_Vec3f)(0.0f);
	switch(l->type)
	{ 
		case RT_AMBIENT_LIGHT:
		{ 
			return (l->c_wi * l->ls);
		}
		case RT_AREA_LIGHT:
		{ 
			//float _dot = dot(-o->normal, l->c_wi);
			//if(_dot > 0.0f)
			return (dot(-o->normal, l->c_wi) > 0.0f) ?
						Emissive_Color(&o->material) :
						(RT_Vec3f)(0.0f);

		}
		case RT_POINT_LIGHT:
		{
			float dist = length(r->lhitPoint - l->point);
			return l->c_wi * (l->ls / pow(dist, l->ex));
			//break;
		}
	}

	//float dist = length(r->lhitPoint - l->position);
	//return l->color * (l->ls / pow(dist, l->ex));
	//return c;
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
		{ }
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
	
	return 0.0f;
}
