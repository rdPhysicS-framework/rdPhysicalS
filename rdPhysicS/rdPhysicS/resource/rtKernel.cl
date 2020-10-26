inline void DisplayPixel(const int x, 
						 const int y, 
						 const int w,
						 const RT_Color *pc, 
						 __global int *bufferImage)
{ 
	int invR = w - x - 1;
	int i = (y * w) + invR;
	*(bufferImage + i) = pc->rgba;
}

RT_Vec3f _render(__global const RT_DataScene *world,
			     __global const RT_Camera *camera,
			     __global const RT_Light *lights,
				 __global const RT_Lamp *lamps,
			     __global const RT_Primitive *objects,
				 const int x, const int y)
{ 
	RT_Vec2f s = world->vp.sp / camera->zoom;
	RT_Vec2f pp = (RT_Vec2f)( s.x * (x - 0.5f * world->vp.width),
								 -s.y * (y - 0.5f * world->vp.height));
	RT_Ray ray = CreateRay(camera->eye, 
						   GetDirectionRayCam(&pp, camera));

	uint seed = get_global_size(0) * y + x + world->seed;
	uint iAlight = RandIndex(&seed, world->numSamples, world->numSets);
	RT_Vec3f pc = Tracer(lights, lamps, objects, world, &ray, iAlight, &seed);

	return pc;	
}


RT_Vec3f Sampler_Render(__global const RT_DataScene *world,
						__global const RT_Camera *camera,
						__global const RT_Light *lights,
						__global const RT_Lamp *lamps,
						__global const RT_Primitive *objects,
						__global const char *sampleShuffledIndices,
						const int x, const int y)
{ 
	RT_Vec3f pc = (RT_Vec3f)(0.0f);
	RT_Vec2f s = world->vp.sp / camera->zoom;
	int n = sqrt((float)world->numSamples);
	uint seed = get_global_size(0) * y + x + world->seed;
	uint i = RandIndex(&seed, world->numSamples, world->numSets);
	uint iAlight = RandIndex(&seed, world->numSamples, world->numSets);

	for(int p = 0; p < n; p++)
	{ 
		for(int q = 0; q < n; q++)
		{
			RT_Vec2f sp;
			switch(world->type)
			{ 
				case RT_HAMMERSLEY:
					sp = HammersleyGenerateSampler(world->numSamples, (int)sampleShuffledIndices[i]);
				break;
				case RT_JITTERED:
					sp = JitteredGenerateSampler(&seed, n, (int)sampleShuffledIndices[i]);
				break;
				case RT_REGULAR:
					sp = RegularGenerateSampler(n, (int)sampleShuffledIndices[i]);
				break;
			}

			RT_Vec2f pp = (RT_Vec2f)( s.x * (x - 0.5f * world->vp.width + sp.x),
									 -s.y * (y - 0.5f * world->vp.height + sp.y));
			RT_Ray ray = CreateRay(camera->eye, 
								   GetDirectionRayCam(&pp, camera));

			pc += Tracer(lights, lamps, objects, world, &ray, iAlight, &seed);
			i++;
			iAlight++;
		}
	}

	pc /= world->numSamples;
	
	return pc;
}

typedef struct
{ 
	float x, y, z;
}vec3;

__kernel void render(__global const RT_DataScene *world,
					 __global const RT_Camera *camera,
					 __global const RT_Light *lights,
					 __global const RT_Lamp *lamps,
				     __global const RT_Primitive *objects,
					 __global const char *sampleShuffledIndices, 
					 __global int *bufferImage)
{
	uint id = get_global_id(0);

	uint x = id % world->vp.width;
	uint y = id / world->vp.width;
	
	RT_Vec3f pc = world->background;

	if(world->numSamples == 1)
	{
		pc = _render(world, camera, lights, lamps, objects, x, y);	
	}
	else
	{ 
		pc = Sampler_Render(world, camera, lights, lamps, objects, sampleShuffledIndices, x, y);
	}

	Saturate(&pc);
	RT_Color color = CreatePixelColorv3(pc);
	DisplayPixel(x, y, world->vp.width, &color, bufferImage);

	//uint2 seed = (uint2)((world->vp.width * (y + 1) + x),
						 //83 + (world->vp.width * (y + 1) + x));
	//uint seed = world->seed + get_global_size(0) * y + x;
	//res[id] = randInt(&seed) % 83;// / (float)RANDMAX;
}
