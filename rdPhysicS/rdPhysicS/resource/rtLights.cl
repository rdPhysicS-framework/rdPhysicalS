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
	float dist = length(r->lhitPoint - l->position);
	return l->color * (l->ls / pow(dist, l->ex));
}

bool InShadow(const RT_Light *l, 
			  __constant RT_Primitive *objects,
			  const int numObj, 
			  const RT_Ray ray)
{	
	float tmin;
	switch(l->type)
	{ 
		case RT_AREA_LIGHT:
			tmin = dot(l->position - ray.o, ray.d);
		break;
		case RT_POINT_LIGHT:
			tmin = length(l->position - ray.o);
		break;
	}

	return ShadowHit(objects, numObj, &ray, tmin); 
}
