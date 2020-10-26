
RT_Vec3f Lambertian_F(const RT_BRDF *brdf)
{ 
	return brdf->color * (brdf->k * INVPI);
}

RT_Vec3f Lambertian_RHO(const RT_BRDF *brdf)
{ 
	return brdf->color * brdf->k;
}

RT_Vec3f GlossySpecular_F(const RT_Result *r, 
						  const RT_Vec3f *wi,
						  const RT_Vec3f *wo)
{ 
	RT_Vec3f l = (RT_Vec3f)(0);
	RT_Vec3f refl = reflect(wi, &r->normal);
	float nDotWo = dot(refl, *wo);

	if(nDotWo > 0.0f)
	{ 
		l = r->material.specular.color * 
			r->material.specular.k *
			(float)pow(nDotWo, r->material.specular.index);
	}

	return l;
}

RT_Vec3f PerfectSpecular_SampleF(const RT_Result *r, 
								 RT_Vec3f *wi,
								 const RT_Vec3f *wo)
{ 
	*wi = reflect(wo, &r->normal);
	return r->material.refl.color * r->material.refl.k / fabs(dot(r->normal, *wi));
}

RT_Vec3f Shade(__global const RT_Light *lights,
			   __global const RT_Primitive *objects,
			   __global const RT_DataScene *world,
			   const RT_Ray *ray,
			   const RT_Result *r)
{ 
	//RT_Vec3f wo = -ray->d;
	RT_Light ambient = lights[0];
	RT_Vec3f color = Lambertian_RHO(&r->material.ambient) * 
					 Color(&ambient, 0, objects, world, r, 0, 0);
	
	for(int i = 1; i < world->numLights; i++)
	{ 
		RT_Light l = lights[i];
		RT_Vec3f wi = Direction(world, &l, 0, r, 0, 0);

		float nDotWi = dot(r->normal, wi);

		if(nDotWi > 0.0f)
		{ 
			RT_Ray auxRay = CreateRay(r->lhitPoint, wi);
			if(!InShadow(&l, objects, world->numObjects, &auxRay))
			{ 
				color += (Lambertian_F(&r->material.diffuse) +
						  GlossySpecular_F(r, &wi, &ray->d))  *
						  Color(&l, 0, 0, 0, r, 0, 0) * nDotWi;
			}
		}
	}

	return color;
}


RT_Vec3f Emissive_Shade(const RT_Ray *ray,
					    const RT_Result *r)
{ 
	return (Emissive_Color(&r->emissiveMaterial) * 
			 r->emissiveMaterial.ls);
	/*return (dot(-r->normal, ray->d) > 0.0f)? 
			(Emissive_Color(&r->emissiveMaterial) * 
			 r->emissiveMaterial.ls)	   :
		   (RT_Vec3f)(0.0f);*/
}

RT_Vec3f Emissive_Color(const RT_Emissive *m)
{ 
	RT_Vec3f c;
	c.x = ((m->color & RMASK) >> RSHIFT) / COLORMAX;
	c.y = ((m->color & GMASK) >> GSHIFT) / COLORMAX;
	c.z = ((m->color & BMASK) >> BSHIFT) / COLORMAX;

	return (c * m->ls);
}

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
						  uint *seed)
{ 
	//RT_Vec3f wo = -ray->d;
	RT_Light ambient = lights[0];
	RT_Vec3f color = Lambertian_RHO(&r->material.ambient) * 
					 Color(&ambient, 0, objects, world, r, 0, 0);
	
	for(int i = 1; i < world->numLights; i++)
	{ 
		RT_Light l = lights[i];
		RT_Lamp o = lamps[l.index];
		RT_Vec3f wi = Direction(world, &l, &o, r, sampleIndex, seed);

		float nDotWi = dot(r->normal, wi);

		if(nDotWi > 0.0f)
		{ 
			RT_Ray auxRay = CreateRay(r->lhitPoint, wi);
			if(!InShadow(&l, objects, world->numObjects, &auxRay))
			{ 
				color += (Lambertian_F(&r->material.diffuse) +
						  GlossySpecular_F(r, &wi, &ray->d))  *
						  Color(&l, &o, 0, 0, r, sampleIndex, seed) * 
						  G(&l, &o, r) *
						  nDotWi / PDF(&o);
			}
		}
	}

	return color;
}

/*----------------------------------------------------------------------------------------------
 *
 * it calculates the effects of the reflection
 * 
 *----------------------------------------------------------------------------------------------*/
RT_Vec3f Reflective_Shade(__global const RT_Light *lights,
						  __global const RT_Lamp *lamps,
						  __global const RT_Primitive *objects,
						  __global const RT_DataScene *world,
						  const RT_Ray *ray,
						  const RT_Result *r)
{ 
	//this
	RT_Vec3f color = Shade(lights, objects, world, ray, r);
	RT_Vec3f wi;
	RT_Vec3f refl = PerfectSpecular_SampleF(r, &wi, &ray->d);
	float d = dot(r->normal, wi);

	//other
	RT_Result otherR;
	RT_Vec3f otherColor = (RT_Vec3f)(0.0f);
	RT_Ray newRay = CreateRay(r->lhitPoint, wi);

	//calculate
	for(int i = 0; i < world->depth; i++)
	{ 
		otherR = Hit(lamps, objects, world->numLamps, 
					 world->numObjects, &newRay);

		if(!otherR.hit)
			break;

		otherColor = (otherR.type == 0)? 
				      Shade(lights, objects, world, &newRay, &otherR) :
					  Emissive_Shade(&newRay, &otherR);

		color += refl * otherColor * d;

		if(otherR.material.type != RT_REFLECTIVE_MATERIAL)
		{
			break;
		}

		refl = PerfectSpecular_SampleF(&otherR, &wi, &newRay.d);
		d = dot(otherR.normal, wi);
		newRay = CreateRay(otherR.lhitPoint, wi);
	}


	return color;
}

RT_Vec3f Reflective_AreaLight_Shade(__global const RT_Light *lights,
									__global const RT_Lamp *lamps,
									__global const RT_Primitive *objects,
									__global const RT_DataScene *world,
									const RT_Ray *ray,
									const RT_Result *r,
									const int sampleIndex,
									uint *seed)
{ 
	//this
	RT_Vec3f color = AreaLight_Shade(lights, lamps, objects, world,
									 ray, r, sampleIndex, seed);
	RT_Vec3f wi;
	RT_Vec3f refl = PerfectSpecular_SampleF(r, &wi, &ray->d);
	float d = dot(r->normal, wi);

	//other
	RT_Result otherR;
	RT_Vec3f otherColor = (RT_Vec3f)(0.0f);
	RT_Ray newRay = CreateRay(r->lhitPoint, wi);

	//calculate
	for(int i = 0; i < world->depth; i++)
	{ 
		otherR = Hit(lamps, objects, world->numLamps, 
					 world->numObjects, &newRay);

		if(!otherR.hit)
			break;

		otherColor = (otherR.type == 0)? 
				      AreaLight_Shade(lights, lamps, objects, world,
									  ray, &otherR, sampleIndex, seed) :
					  Emissive_Shade(&newRay, &otherR);

		color += refl * otherColor * d;

		if(otherR.material.type != RT_REFLECTIVE_MATERIAL)
		{
			break;
		}

		refl = PerfectSpecular_SampleF(&otherR, &wi, &newRay.d);
		d = dot(otherR.normal, wi);
		newRay = CreateRay(otherR.lhitPoint, wi);
	}


	return color;
}