
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

/*RT_Vec3f BRDF_F(const RT_BRDF *brdf,
			    const RT_Vec3f *normal,
				const RT_Vec3f *wi,
				const RT_Vec3f *wo)
{ 
	switch(brdf->type)
	{ 
		case RT_GLOSSY_SPECULAR:
			return GlossySpecular_F(brdf, normal, wi, wo);
		break;
		case RT_LAMBERTIAN:
			return Lambertian_F(brdf);
		break;
		case RT_PERFECT_SPECULAR:
			PerfectSpecular_SampleF(brdf, normal, wi, wo);
		break;
	}

	RT_Vec3f v = (RT_Vec3f)(0);
	return v;
}*/

RT_Vec3f Shade(__global const RT_Light *lights,
			   __global const RT_Primitive *objects,
			   __global const RT_DataScene *world,
			   const RT_Ray *ray,
			   const RT_Result *r)
{ 
	//RT_Vec3f wo = -ray->d;
	RT_Light ambient = lights[0];
	RT_Vec3f color = Lambertian_RHO(&r->material.ambient) * 
					 Color(&ambient, r);
	
	for(int i = 1; i < world->numLights; i++)
	{ 
		RT_Light l = lights[i];
		RT_Vec3f wi = Direction(&l, r);

		float nDotWi = dot(r->normal, wi);

		if(nDotWi > 0.0f)
		{ 
			if(!InShadow(&l, objects, world->numObjects, 
					     CreateRay(r->lhitPoint, wi))  )
			{ 
				color += (Lambertian_F(&r->material.diffuse) +
						  GlossySpecular_F(r, &wi, &ray->d))  *
						  Color(&l, r) * nDotWi;
			}
		}
	}

	return color;
}
