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
