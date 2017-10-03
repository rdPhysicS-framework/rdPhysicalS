#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <time.h>
#include "src\assets\Info.h"
#include "src\assets\RT_Util.h"
#include "src\Transform.h"
#include "src\Tringles\Grid.h"

static cl_int SetPlatforms(std::vector<cl_platform_id> &platforms)
{
	cl_uint num = 0;
	cl_int status = clGetPlatformIDs(0, nullptr, &num);
	if (status != CL_SUCCESS)
		return -1;

	cl_platform_id *p = new cl_platform_id[num];
	status = clGetPlatformIDs(num, p, nullptr);
	if (status != CL_SUCCESS)
		return -1;

	platforms.assign(&p[0], &p[num]);

	for (cl_platform_id id : platforms)
	{
		displayPlatformInfo(id, CL_PLATFORM_NAME, "CL_PLATFORM_NAME");
	}
	std::cout << std::endl;
	return CL_SUCCESS;
}

static cl_int SetDevices(const cl_platform_id platform, 
						 const cl_device_type type,
						 std::vector<cl_device_id> &devices)
{
	cl_uint num = 0;
	cl_int status = clGetDeviceIDs(platform, type, 0, nullptr, &num);
	if (status != CL_SUCCESS)
		return -1;

	cl_device_id *ids = new cl_device_id[num];
	status = clGetDeviceIDs(platform, type, num, ids, nullptr);
	if (status != CL_SUCCESS)
		return -1;

	devices.assign(&ids[0], &ids[num]);

	for (cl_device_id id : devices)
	{
		displayDeviceDetails(id, CL_DEVICE_NAME, "CL_DEVICE_NAME");
		displayDeviceDetails(id, CL_DEVICE_MAX_COMPUTE_UNITS, "CL_DEVICE_NAME");
		displayDeviceDetails(id, CL_DEVICE_MAX_WORK_GROUP_SIZE, "CL_DEVICE_NAME");
	}
	std::cout << std::endl;
	return CL_SUCCESS;
}

int Option(int size)
{
	if (size == 1)
		return 0;

	int input = 1;

	std::cout << "Choice one of the options!" << std::endl
		      << "Option: ";
	std::cin >> input;

	while (input < 1 || input > size)
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail(), '\n');
		std::cout << "No such option. Choose again!" << std::endl <<"nOption: ";
		std::cin >> input;
	}

	return input - 1;
}

cl_program CreateClProgram(const cl_context context,
						   std::initializer_list<std::string> kernels)
{
	char *source = nullptr;
	size_t sourceSize;

	try
	{
		std::string s = RT::LoadSource(kernels);
		source = const_cast<char*>(s.c_str());
		sourceSize = s.size();
		//std::cout << s << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << "\nFailed to load kernel." << std::endl;
		system("pause");
		exit(1);
	}

	int status;
	cl_program p = clCreateProgramWithSource(context, 1, (const char**)&source, (const size_t*)&sourceSize, &status);
	/*tratar erro*/
	return p;
}

static Program CreateProgram()
{
	Program prog;
	std::vector<cl_platform_id> platforms;
	SetPlatforms(platforms);

	int p = Option(platforms.size());
	prog.platform = platforms[p];

	std::vector<cl_device_id> devices;
	SetDevices(prog.platform, CL_DEVICE_TYPE_ALL, devices);

	int d = Option(devices.size());
	prog.device = devices[d];

	cl_int status;
	prog.context = clCreateContext(nullptr, 1, &prog.device, nullptr, nullptr, &status);
	prog.queue = clCreateCommandQueue(prog.context, prog.device, 0, &status);

	prog.program = CreateClProgram(prog.context, 
								  { PATH"rtUtil.cl",
									PATH"rtStructs.cl",
									PATH"rtMaterial.cl",
									PATH"rtGeometricObject.cl",
									PATH"rtLights.cl",
									PATH"rtWorld.cl",
									PATH"rtKernel.cl" });

	return prog;
}

void DetailsProgram(const Program &program)
{
	std::cout << std::endl;
	displayPlatformInfo(program.platform, CL_PLATFORM_NAME, "CL_PLATFORM_NAME");

	displayDeviceDetails(program.device, CL_DEVICE_NAME, "CL_DEVICE_NAME");
	displayDeviceDetails(program.device, CL_DEVICE_MAX_COMPUTE_UNITS, "CL_DEVICE_MAX_COMPUTE_UNITS");
	displayDeviceDetails(program.device, CL_DEVICE_MAX_WORK_GROUP_SIZE, "CL_DEVICE_MAX_WORK_GROUP_SIZE");
	std::cout << std::endl;
}

int Save(const int *image, const int w, const int h)
{
	if (!image)
		return -1;

	SDL_Surface *img = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	if (!img)
		return -1;
	
	img->pixels = (cl_uint*)image;
	IMG_SavePNG(img, FILE_NAME);
	
	//SDL_FreeSurface(img);

	return 0;
}

void setObjects(RT_Primitive *objects)
{
	//RT::Mat4f m;

	objects[0].p = { 162, 54, 432 };
	objects[0].s = { 0, 0, 0 };
	objects[0].r = 216;
	objects[0].material = { { { 0.6f, 0.6f, 0.6f }, 0.2f, 0,    RT_LAMBERTIAN },
						    { { 0.6f, 0.6f, 0.6f }, 0.7f, 0,    RT_LAMBERTIAN },
						    { { 0.6f, 0.6f, 0.6f }, 0.8f, 1.0f, RT_GLOSSY_SPECULAR },
						    { { 0.6f, 0.6f, 0.6f }, 0.0f, 0,    RT_PERFECT_SPECULAR } };
	objects[0].type = RT_SPHERE;
	objects[0].bbox = { objects[0].p.x - (objects[0].r*objects[0].r+4),
						objects[0].p.y - (objects[0].r*objects[0].r+4),
						objects[0].p.z - (objects[0].r*objects[0].r+4),
						objects[0].p.x + (objects[0].r*objects[0].r+4),
						objects[0].p.y + (objects[0].r*objects[0].r+4),
						objects[0].p.z + (objects[0].r*objects[0].r+4) };
	rdPhs::Transform *t = rdPhs::Transform::Get();
	/*t->CopyTransformMatrix(objects[0].invMatrix);
	t->Scale(1, 2.0f, 1)
	  .RotateX(-90.0f)
	  .Translate(162, 54, 432)
	  .CopyTransformMatrix(objects[0].invMatrix);//.invMatrix[0]);*/
	/*m = RT::mt4::AffScaling(1, 1/2.0f, 1) * 
		RT::mt4::AffRotationX(
			RT::Math::ToRadians(-90.0f))
							.Transpose() * 
		RT::mt4::AffTranslation(-162, -54, -432);

	memcpy(objects[0].invMatrix, (void*)m.GetMatrix(), sizeof(objects[0].invMatrix));*/
	

	objects[1].p = { -540, -86, 432 };
	objects[1].s = { 0, 0, 0 };
	objects[1].r = 270;
	objects[1].material = { {{ 0.7f, 0.7f, 1.0f }, 0.2f, 0,    RT_LAMBERTIAN}, 
							{{ 0.7f, 0.7f, 0.7f }, 0.7f, 0,    RT_LAMBERTIAN },
							{{ 0.7f, 0.7f, 0.7f }, 0.8f, 1.0f, RT_GLOSSY_SPECULAR },
							{{ 0.0f, 0.0f, 0.0f }, 0.0f, 0,    RT_PERFECT_SPECULAR} };
	objects[1].type = RT_SPHERE;
	//memcpy(objects[1].invMatrix, (void*)m.GetMatrix(), sizeof(objects[1].invMatrix));
	t->CopyTransformMatrix(objects[1].invMatrix);
	objects[1].bbox = { objects[1].p.x - (objects[1].r*objects[1].r + 4),
						objects[1].p.y - (objects[1].r*objects[1].r + 4),
						objects[1].p.z - (objects[1].r*objects[1].r + 4),
						objects[1].p.x + (objects[1].r*objects[1].r + 4),
						objects[1].p.y + (objects[1].r*objects[1].r + 4),
						objects[1].p.z + (objects[1].r*objects[1].r + 4) };

	objects[2].p = { 0, -324, 270 };
	objects[2].s = { 324, 162, 324 };
	objects[2].r = 0;
	objects[2].material = { { { 0.7f, 0.7f, 1.0f }, 0.2f, 0,    RT_LAMBERTIAN },
							{ { 0.7f, 0.7f, 1.0f }, 0.7f, 0,    RT_LAMBERTIAN },
							{ { 0.7f, 0.7f, 1.0f }, 0.2f, 1.0f, RT_GLOSSY_SPECULAR },
							{ { 0.7f, 0.7f, 1.0f }, 0.0f, 0,    RT_PERFECT_SPECULAR } };
	objects[2].type = RT_BOX;

	RT_Vec3f aux = objects[2].p + objects[2].s;
	float r = (aux.x > aux.y) ? aux.x : aux.y;
	r = (aux.z > r) ? aux.z : r;

	float x0 = objects[2].p.x;
	float y0 = objects[2].p.y;
	float z0 = objects[2].p.z;
	float x1 = objects[2].p.x + r;
	float y1 = objects[2].p.y + r;
	float z1 = objects[2].p.z + r;

	objects[2].bbox = { x0, y0, z0,
						x1, y1, z1};

	//memcpy(objects[2].invMatrix, (void*)m.GetMatrix(), sizeof(objects[2].invMatrix));
	t->CopyTransformMatrix(objects[2].invMatrix);

}

void setScene(RT_Primitive *planes)
{
	planes[0] = { { 0, -324, 0 }, { 0,  1,  0 }, 0, 
				  { { {0.4f, 0.3f, 0.3f}, 0.2f, 0, RT_LAMBERTIAN }, 
					{ {0.4f, 0.3f, 0.3f}, 0.7f, 0, RT_LAMBERTIAN },
					{ {0.4f, 0.3f, 0.3f}, 0.5f, 1.0f, RT_GLOSSY_SPECULAR },
					{ {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f, RT_PERFECT_SPECULAR } },
				    RT_PLANE};
	planes[1] = { { 0, 0, 2419 },{ 0,  0, -1 }, 0, 
				  { { { 0.6f, 0.5f, 0.5f }, 0.2f, 0, RT_LAMBERTIAN },
				    { { 0.6f, 0.5f, 0.5f }, 0.7f, 0, RT_LAMBERTIAN },
				    { { 0.6f, 0.5f, 0.5f }, 0.5f, 1.0f, RT_GLOSSY_SPECULAR },
				    { { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, RT_PERFECT_SPECULAR } },
					RT_PLANE };
	planes[2] = { { -1296, 0, 0 },{ 1,  0,  0 }, 0, 
				  { { { 0.5f, 0.6f, 0.6f }, 0.2f, 0, RT_LAMBERTIAN },
				    { { 0.5f, 0.6f, 0.6f }, 0.7f, 0, RT_LAMBERTIAN },
				    { { 0.5f, 0.6f, 0.6f }, 0.5f, 1.0f, RT_GLOSSY_SPECULAR },
				    { { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, RT_PERFECT_SPECULAR } },
				  	RT_PLANE };
	planes[3] = { { 1296, 0, 0 },{ -1,  0,  0 }, 0, 
				  { { { 0.5f, 0.6f, 0.6f }, 0.2f, 0, RT_LAMBERTIAN },
				    { { 0.5f, 0.6f, 0.6f }, 0.7f, 0, RT_LAMBERTIAN },
				    { { 0.5f, 0.6f, 0.6f }, 0.5f, 1.0f, RT_GLOSSY_SPECULAR },
				    { {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f, RT_PERFECT_SPECULAR } },
				  	RT_PLANE };
	planes[4] = { { 0, 800, 0 },{ 0, -1,  0 }  , 0, 
				  { { { 0.7f, 0.7f, 0.7f }, 0.2f, 0, RT_LAMBERTIAN },
				    { { 0.7f, 0.7f, 0.7f }, 0.7f, 0, RT_LAMBERTIAN },
				    { { 0.7f, 0.7f, 0.7f }, 0.5f, 1.0f, RT_GLOSSY_SPECULAR },
				    { { 0.7f, 0.7f, 0.7f }, 0.0f, 0.0f, RT_PERFECT_SPECULAR } },
				  	RT_PLANE };
}

void setLights(RT_Light *lights)
{
	lights[0].position = { 162.0f, 756.0f, 432.0f };
	lights[0].color = { 1, 1, 1};
	lights[0].ls = 1.0f;
	lights[0].ex = 0.0f;
	lights[0].type = RT_POINT_LIGHT;

	lights[1].position = { -540.0f, 756.0f, 432.0f };
	lights[1].color = { 1, 1, 1 };
	lights[1].ls = 1.0f;
	lights[1].ex = 0.0f;
	lights[1].type = RT_POINT_LIGHT;
}

int main(int argc, char **argv)
{
	Program program = CreateProgram();
	DetailsProgram(program);
	program.BildProgram();

	/*input*/
	const int numObjects = 3;
	RT_Primitive objects[numObjects];
	setObjects(objects);

	const int numPlanes = 5;
	RT_Primitive p[numPlanes];
	setScene(p);

	std::vector<RT_Primitive> prim;

	for (int i = 0; i < numPlanes; i++)
	{
		prim.push_back(p[i]);
	}
	for (int i = 0; i < numObjects; i++)
	{
		prim.push_back(objects[i]);
	}

	//rdPhs::Grid *g = new rdPhs::Grid(&prim);
	//g->SetupCells();

	const int numLights = 2;
	RT_Light lights[numLights];
	setLights(lights);

	RT_ViewPlane vp = { WIDTH_CANVAS, HEIGHT_CANVAS, { 1, 1 } };
	RT_Camera camera = { { -702, -108, -270 },
						 { -540, -100, 0 },
						 { 0, 1.0f, 0 },
						 800, 1.5f, 0, 1,
						 {},{},{} };
	camera.computeUVW();

	RT_DataScene world = { vp, {0, 0, 0}, numLights, prim.size() };

	/*output*/
	const int sizeBuffer = WIDTH_CANVAS * HEIGHT_CANVAS;
	int *bufferImage = new int[sizeBuffer];

	cl_int status;
	cl_kernel kernel = clCreateKernel(program.program, "render", &status);
	
	cl_mem mem_world = clCreateBuffer(program.context, CL_MEM_WRITE_ONLY, sizeof(RT_DataScene), nullptr, &status);
	/*se houver, tratar erro*/
	cl_mem mem_camera = clCreateBuffer(program.context, CL_MEM_WRITE_ONLY, sizeof(RT_Camera), nullptr, &status);
	/*se houver, tratar erro*/
	cl_mem mem_lights = clCreateBuffer(program.context, CL_MEM_WRITE_ONLY, sizeof(RT_Light)*numLights, nullptr, &status);
	/*se houver, tratar erro*/
	cl_mem mem_input = clCreateBuffer(program.context, CL_MEM_WRITE_ONLY, sizeof(RT_Primitive)*prim.size(), nullptr, &status);
	/*se houver, tratar erro*/
	cl_mem mem_output = clCreateBuffer(program.context, CL_MEM_READ_ONLY, sizeof(int)*sizeBuffer, nullptr, &status);
	/*se houver, tratar erro*/
	
	status = clEnqueueWriteBuffer(program.queue, mem_world, CL_TRUE, 0, sizeof(RT_DataScene), &world, 0, nullptr, nullptr);
	/*se houver, tratar erro*/
	status = clEnqueueWriteBuffer(program.queue, mem_camera, CL_TRUE, 0, sizeof(RT_Camera), &camera, 0, nullptr, nullptr);
	/*se houver, tratar erro*/
	status = clEnqueueWriteBuffer(program.queue, mem_lights, CL_TRUE, 0, sizeof(RT_Light)*numLights, lights, 0, nullptr, nullptr);
	/*se houver, tratar erro*/
	status = clEnqueueWriteBuffer(program.queue, mem_input, CL_TRUE, 0, sizeof(RT_Primitive)*prim.size(), prim.data(), 0, nullptr, nullptr);
	/*se houver, tratar erro*/

	//status  = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&mem_vp);
	//status |= clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&mem_cam);
	status  = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&mem_world);
	status |= clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&mem_camera);
	status |= clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&mem_lights);
	status |= clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&mem_input);
	status |= clSetKernelArg(kernel, 4, sizeof(cl_mem), (void*)&mem_output);
	/*se houver, tratar erro*/

	//status = clEnqueueTask(program.queue, kernel, 0, nullptr, nullptr);
	/*se houver, tratar erro*/
	size_t paramSize;
	status = clGetDeviceInfo(program.device, CL_DEVICE_MAX_WORK_GROUP_SIZE, 0, nullptr, &paramSize);
	size_t *ret = new size_t[paramSize];
	status = clGetDeviceInfo(program.device, CL_DEVICE_MAX_WORK_GROUP_SIZE, paramSize, ret, nullptr);
	/*define o numero de itens global*/
	size_t globalItemSize = sizeBuffer;
	/*define o maximo de itens em um grupo de trabalho*/
	size_t localItemSize = *ret;

	std::cout << "Kernel work group size: " << localItemSize << std::endl;

	if (globalItemSize % localItemSize != 0)
		globalItemSize = (globalItemSize / localItemSize + 1) * localItemSize;

	std::cout << "Global groupe size: " << globalItemSize << std::endl;
	
	status = clEnqueueNDRangeKernel(program.queue, kernel, 1, nullptr, &globalItemSize, nullptr, 0, nullptr, nullptr);
	/*se houver, tratar erro*/

	status = clEnqueueReadBuffer(program.queue, mem_output, CL_TRUE, 0, sizeof(int)*sizeBuffer, bufferImage, 0, nullptr, nullptr);
	/*se houver, tratar erro*/

	status  = clReleaseKernel(kernel);
	status |= clReleaseMemObject(mem_world);
	status |= clReleaseMemObject(mem_camera);
	status |= clReleaseMemObject(mem_lights);
	status |= clReleaseMemObject(mem_input);
	status |= clReleaseMemObject(mem_output);

	/*se houver, tratar erro*/
	status = Save(bufferImage, WIDTH_CANVAS, HEIGHT_CANVAS);
	if (status != CL_SUCCESS)
		std::cerr << "ERRO ao salvar a imagem\n";

	system("pause");
	return 0;
}