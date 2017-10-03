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

__kernel void render(__constant RT_DataScene *world,
					 __constant RT_Camera *camera,
					 __global const RT_Light *lights,
				     __constant RT_Primitive *objects, 
					 __global int *bufferImage)
{
	RT_Vec2f s = world->vp.sp / camera->zoom;
	uint id = get_global_id(0);

	uint x = id % world->vp.width;
	uint y = id / world->vp.width;
	
	RT_Vec2f pp = (RT_Vec2f)( s.x * (x - 0.5f * world->vp.width),
							 -s.y * (y - 0.5f * world->vp.height));
	RT_Ray ray = CreateRay(camera->eye, 
						   GetDirectionRayCam(&pp, camera));

	RT_Vec3f pc = TraceRay(lights, objects, world, &ray);
	Saturate(&pc);
	RT_Color color = CreatePixelColorv3(pc);
	DisplayPixel(x, y, world->vp.width, &color, bufferImage);
	
	/*uint2 seed = (uint2)((world->vp.width * (y + 1) + x),
						 83 + (world->vp.width * (y + 1) + x));*/
	//uint seed = get_global_size(0) * y + x;
	//outRand[id] = randFloat2(&seed, 0, 1.0f/100);// / (float)RANDMAX;
}
