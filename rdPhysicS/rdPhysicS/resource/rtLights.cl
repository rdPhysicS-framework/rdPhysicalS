/*----------------------------------------------------------------------------------------------
 *
 * Methods of the PointLight
 *
 *----------------------------------------------------------------------------------------------*/
 RT_Light Create_PointLight(const RT_Vec3f p, const RT_Vec3f c, const float ls)
 {
	RT_Light l;
	l.position = p;
	l.color = c;
	l.ls = ls;
	return l;
 }

inline RT_Vec3f Direction(const RT_Light *l, const RT_Result *r)
{
	return normalize(l->position - r->lhitPoint);
}

inline RT_Vec3f Color(const RT_Light *l, const RT_Result *r)
{
	//RT_Vec3f c = (RT_Vec3f)(0.0f);
	switch(l->type)
	{ 
		case RT_AMBIENT_LIGHT:
		{ 
			return (l->color * l->ls);
		}
		case RT_AREA_LIGHT:
		{ 
			return (RT_Vec3f)(0.0f);
		}
		case RT_POINT_LIGHT:
		{
			float dist = length(r->lhitPoint - l->position);
			return l->color * (l->ls / pow(dist, l->ex));
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
			  const RT_Ray ray)
{	
	float tmin;
	switch(l->type)
	{ 
		case RT_AMBIENT_LIGHT:
		break;
		case RT_AREA_LIGHT:
			tmin = dot(l->position - ray.o, ray.d);
		break;
		case RT_POINT_LIGHT:
			tmin = length(l->position - ray.o);
		break;
	}

	return ShadowHit(objects, numObj, &ray, tmin); 
}
