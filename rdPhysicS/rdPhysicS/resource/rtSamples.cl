uint RandIndex(uint *seed,
			   const int numSamples,
			   const int numSets)
{ 
	return (randInt(seed) % numSets * numSamples);
}

/*----------------------------------------------------------------------------------------------
 *
 * Methods for the generation of the regular sampler
 *
 *----------------------------------------------------------------------------------------------*/
RT_Vec2f RegularGenerateSampler(const int n,
							    const int id)
{ 
	int x = id % n;
	int y = id / n;

	return (RT_Vec2f)((x + 0.5f)/n,
	                  (y + 0.5f)/n);
}

/*----------------------------------------------------------------------------------------------
 *
 * Method for the generation of the Jittered sampler
 *
 *----------------------------------------------------------------------------------------------*/
 RT_Vec2f JitteredGenerateSampler(uint *seed,
								  const int n,
							      const int id)
{ 
	int x = id % n;
	int y = id / n;

	return (RT_Vec2f)((x + randFloat(seed))/n,
	                  (y + randFloat(seed))/n);
}

/*----------------------------------------------------------------------------------------------
 *
 * Method for the generation of the Hammersley sampler
 *
 *----------------------------------------------------------------------------------------------*/
RT_Vec2f HammersleyGenerateSampler(const int numSamples,
							       const int id)
{ 
	return (RT_Vec2f)((float)id / numSamples,
	                   Phi(id));
}

float Phi(int index)
{ 
	float x = 0.0f;
	float f = 0.5f;

	while(index != 0)
	{ 
		x += f * (float)(index % 2);
		index /= 2;
		f *= 0.5f;
	}

	return x;
}

void MapSampleToUnitDisk(RT_Vec2f *d)
{ 
	float x, y, r, phi;

	x = 2 * (*d).x - 1.0f;
	y = 2 * (*d).y - 1.0f;

	if(x > -y)
	{ 
		if(x > y)
		{ 
			r = x;
			phi = y / x;
		}
		else
		{ 
			r = y;
			phi = 2 - x / y;
		}
	}
	else
	{ 
		if(x < y)
		{ 
			r = -x;
			phi = 4 + y / x;
		}
		else
		{ 
			r = -y;
			phi = (y != 0.0f) ? 6 - x / y : 0.0f;
		}
	}

	phi *= PI / 4.0f;

	(*d).x = r * cos(phi);
	(*d).y = r * sin(phi);
}

RT_Vec3f MapSampleToSphere(RT_Vec2f *d)
{ 
	float z = 1.0f - 2.0f * (*d).x;

	float r = sqrt(1.0f - z * z);
	float phi = PI2 * (*d).y;

	return (RT_Vec3f)((*d).x * cos(phi), 
				      (*d).y * sin(phi),
					  z);
}

RT_Vec3f MapSampleToHemisphere(RT_Vec2f *d, const float e)
{ 
	float cosPhi = cos(2.0f * PI * (*d).x);
	float sinPhi = sin(2.0f * PI * (*d).x);

	float cosTheta = pow((1.0f - (*d).y), 1.0f / (e + 1.0f));
	float sinTheta = sqrt(1.0f - cosTheta * cosTheta);

	return (RT_Vec3f)(sinTheta * cosPhi,
					  sinTheta * sinPhi,
					  cosTheta);
}
