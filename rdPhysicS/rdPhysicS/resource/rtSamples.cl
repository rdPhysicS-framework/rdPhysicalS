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

	x = 2 * d->x - 1.0f;
	y = 2 * d->y - 1.0f;

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

	d->x = r * cos(phi);
	d->y = r * sin(phi);
}
