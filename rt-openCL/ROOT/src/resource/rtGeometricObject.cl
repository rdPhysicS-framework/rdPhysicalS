/*----------------------------------------------------------------------------------------------
 *
 * Result
 *
 *----------------------------------------------------------------------------------------------*/
inline RT_Result CreateResult()
{ 
	RT_Result r;
	r.hit = false;
	return r;
}

/*----------------------------------------------------------------------------------------------
 *
 * Methods to verify intercession with the sphere
 *
 *----------------------------------------------------------------------------------------------*/

bool Sphere_Hit(const RT_Primitive *s, const RT_Ray *ray, float *tmin, RT_Result *r)
{
	if(Sphere_ShadowHit(s, ray, tmin))
	{
		RT_Vec3f temp = ray->o - s->p;
		r->normal = (temp + (ray->d * *tmin)) / s->r;
		r->lhitPoint = HitPoint(ray, *tmin);
		return true;
	}

	return false;
}

bool Sphere_ShadowHit(const RT_Primitive *s, const RT_Ray *ray, float *tmin)
{
	RT_Vec3f temp = ray->o - s->p;
	float a = dot(ray->d, ray->d);
	float b = 2.0 * dot(temp, ray->d);
	float c = dot(temp, temp) - (s->r * s->r);
	float disc = b * b - 4.0 * a * c;

	if(disc < 0.0)
		return false;

	float e = sqrt(disc);
	float denom = 2.0 * a;
	float t = (-b - e) / denom;

	if(t > EPSILON)
	{
		*tmin = t;
		return true;
	}

	t = (-b + e) / denom;

	if(t > EPSILON)
	{
		*tmin = t;
		return true;
	}

	return false;
}

/*----------------------------------------------------------------------------------------------
 *
 * Methods to verify intercession with the plane
 *
 *----------------------------------------------------------------------------------------------*/

bool Plane_Hit(const RT_Primitive *p, 
			   const RT_Ray *ray, 
			   float *tmin, RT_Result *r)
{ 
	if(Plane_ShadowHit(p, ray, tmin))
	{ 
		r->normal = p->s_n;
		r->lhitPoint = HitPoint(ray, *tmin);
		return true;
	}

	return false;
}

bool Plane_ShadowHit(const RT_Primitive *p, 
					 const RT_Ray *ray, 
					 float *tmin)
{ 
	float t = dot((p->p - ray->o), p->s_n) / dot(ray->d, p->s_n);

	if(t > EPSILON)
	{ 
		*tmin = t;
		return true;
	}

	return false;
}

/*----------------------------------------------------------------------------------------------
 *
 * Methods to verify intercession with the Cube
 *
 *----------------------------------------------------------------------------------------------*/
RT_Vec3f Box_Normal(const RT_Primitive *b, 
					const RT_Vec3f *p)
{ 
	float d[6];
	d[0] = fabs(b->s_n.x - b->p.x);
	d[1] = fabs(b->s_n.x + b->s_n.x - b->p.x);
	d[2] = fabs(b->s_n.y - b->p.y);
	d[3] = fabs(b->s_n.y + b->s_n.y - b->p.y);
	d[4] = fabs(b->s_n.z - b->p.z);
	d[5] = fabs(b->s_n.z + b->s_n.z - b->p.z);

	int f = 0;
	float t = d[0];
	for(int i = 1; i < 6; i++)
	{
		if(d[i] < t)
		{
			t = d[i];
			f = i;
		}
	}

	return (f == 0) ? (RT_Vec3f)(-1.0f,  0.0f,  0.0f) :
		   (f == 1) ? (RT_Vec3f)( 1.0f,  0.0f,  0.0f) :
		   (f == 2) ? (RT_Vec3f)( 0.0f, -1.0f,  0.0f) :
		   (f == 3) ? (RT_Vec3f)( 0.0f,  1.0f,  0.0f) :
		   (f == 4) ? (RT_Vec3f)( 0.0f,  0.0f, -1.0f) :
		              (RT_Vec3f)( 0.0f,  0.0f,  1.0f)  ;
}

bool Box_Hit(const RT_Primitive *b, 
			 const RT_Ray *ray, 
			 float *tmin, RT_Result *r)
{ 
	if(Box_ShadowHit(b, ray, tmin))
	{ 
		r->lhitPoint = HitPoint(ray, *tmin);
		r->normal = Box_Normal(b, &r->lhitPoint);
		return true;
	}

	return false;
}

bool Box_ShadowHit(const RT_Primitive *b, 
				   const RT_Ray *ray, 
				   float *tmin)
{ 
	float t[6];
	RT_Vec3f ip[6];

	RT_Vec3f d = ray->d;
	RT_Vec3f o = ray->o;

	bool hit = false;

	for (int i = 0; i < 6; i++)
	{
		t[i] = -1;
	}

	RT_Vec3f s = b->p + b->s_n;

	if(d.x)
	{
		float rc = 1.0f / d.x;
		t[0] = (b->p.x - o.x) * rc;
		t[3] = (s.x - o.x) * rc;
	}
	if(d.y)
	{
		float rc = 1.0f / d.y;
		t[1] = (b->p.y - o.y) * rc;
		t[4] = (s.y - o.y) * rc;
	}
	if(d.z)
	{
		float rc = 1.0f / d.z;
		t[2] = (b->p.z - o.z) * rc;
		t[5] = (s.z - o.z) * rc;
	}

	for(int i = 0; i < 6; i++)
	{
		if(t[i] > 0)
		{
			ip[i] = o + d * t[i];

			if ((ip[i].x > (b->p.x - EPSILON)) && (ip[i].x < (s.x + EPSILON)) &&
				(ip[i].y > (b->p.y - EPSILON)) && (ip[i].y < (s.y + EPSILON)) &&
				(ip[i].z > (b->p.z - EPSILON)) && (ip[i].z < (s.z + EPSILON)))
			{
				if(t[i] < *tmin)
				{
					*tmin = t[i];
					hit = true;
				}
			}
		}
	}

	return hit;
}

/*----------------------------------------------------------------------------------------------
 *
 * Method that verifies collision of transformed objects
 *
 *----------------------------------------------------------------------------------------------*/
bool Instance_Hit(const RT_Primitive *object,
				  const RT_Ray *ray,
				  float *tmin,
				  RT_Result *r)
{ 
	if(object->type == RT_BOX || object->type == RT_SPHERE)
	{
		RT_Ray invRay = CreateRay(TransformPoint(&object->invMatrix, &ray->o),
								  TransformDirection(&object->invMatrix, &ray->d));

		if(Box_Hit(object, &invRay, tmin, r) ||
		   Sphere_Hit(object, &invRay, tmin, r))
		{ 
			RT_Mat4f matrix = inverse(&matrix);
			r->lhitPoint = TransformPoint(&object->invMatrix, &r->lhitPoint);
			r->normal = TransformNormal(&object->invMatrix, &r->normal);
			return true;
		}

	}
	else
	{ 
		if(Plane_Hit(object, ray, tmin, r))
			return true;
	}
	return false;
}

 bool Instance_ShadowHit(const RT_Primitive *object, 
						 const RT_Ray *ray, 
						 float *tmin)
{ 
	if(object->type == RT_BOX || object->type == RT_SPHERE)
	{
		RT_Ray invRay = CreateRay(TransformPoint(&object->invMatrix, &ray->o),
								  TransformDirection(&object->invMatrix, &ray->d));
		if(Box_ShadowHit(object, &invRay, tmin) ||
		   Sphere_ShadowHit(object, &invRay, tmin))
			return true;
	}
	else
	{ 
		if(Plane_ShadowHit(object, ray, tmin))
			return true;
	}
	return false;
}