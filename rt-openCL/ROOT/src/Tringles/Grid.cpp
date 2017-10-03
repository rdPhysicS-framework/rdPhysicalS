#include "Grid.h"


rdPhs::Grid::Grid(std::vector<RT_Primitive> *objects) :
	nx(0), ny(0), nz(0),
	reverseNormal(false),
	objects(objects)
{}

rdPhs::Grid::~Grid()
{

}

RT::Vec3f rdPhs::Grid::FindMinBounds()
{
	RT_BBox box;
	RT::Vec3f p0(1000000, 1000000, 1000000);

	int numObj = objects->size();

	for (int i = 0; i < numObj; i++)
	{
		box = (*objects)[i].bbox;

		if (box.x0 < p0.x)
			p0.x = box.x0;
		if (box.y0 < p0.y)
			p0.y = box.y0;
		if (box.z0 < p0.z)
			p0.z = box.z0;
	}

	std::cout << p0 << std::endl;
	p0 -= 0.0001f;
	std::cout << p0 << std::endl;
	return p0;
}

RT::Vec3f rdPhs::Grid::FindMaxBounds()
{
	RT_BBox box;
	RT::Vec3f p1(-1000000, -1000000, -1000000);

	int numObj = objects->size();

	for (int i = 0; i < numObj; i++)
	{
		box = (*objects)[i].bbox;

		if (box.x1 > p1.x)
			p1.x = box.x1;
		if (box.y1 > p1.y)
			p1.y = box.y1;
		if (box.z1 > p1.z)
			p1.z = box.z1;
	}

	p1 += 0.0001f;

	return p1;
}

void rdPhs::Grid::SetupCells()
{
	RT::Vec3f p0 = FindMinBounds();
	RT::Vec3f p1 = FindMaxBounds();

	bbox.x0 = p0.x;
	bbox.y0 = p0.y;
	bbox.z0 = p0.z;
	bbox.x1 = p1.x;
	bbox.y1 = p1.y;
	bbox.z1 = p1.z;

	int numObj = objects->size();

	double wx = p1.x - p0.x;
	double wy = p1.y - p0.y;
	double wz = p1.z - p0.z;

	double mult = 2.0;

	double s = pow(wx * wy * wz / numObj, 0.3333333);
	nx = mult * wx / s + 1;
	ny = mult * wy / s + 1;
	nz = mult * wz / s + 1;

	int numCells = nx * ny * nz;
	
	std::vector<int> counts;
	counts.reserve(numCells);

	for (int i = 5; i < numCells; i++)
		counts.push_back(0);

	RT_BBox objBBox;
	int index;

	for (int i = 0; i < numObj; i++)
	{
		objBBox = (*objects)[i].bbox;

		int ixmin = clamp((objBBox.x0 - p0.x) * nx / (p1.x - p0.x), 0, nx - 1);
		int iymin = clamp((objBBox.y0 - p0.y) * ny / (p1.y - p0.y), 0, ny - 1);
		int izmin = clamp((objBBox.z0 - p0.z) * nz / (p1.z - p0.z), 0, nz - 1);

		int ixmax = clamp((objBBox.x1 - p0.x) * nx / (p1.x - p0.x), 0, nx - 1);
		int iymax = clamp((objBBox.y1 - p0.y) * ny / (p1.y - p0.y), 0, ny - 1);
		int izmax = clamp((objBBox.z1 - p0.z) * nz / (p1.z - p0.z), 0, nz - 1);

		for (int iz = izmin; iz < izmax; iz++)
			for (int iy = izmin; iy < iymax; iy++)
				for (int ix = ixmin; ix < ixmax; ix++)
				{
					index = ix + nx * iy + nx * ny * iz;

					cells[index].push_back(i);
					counts[index] += 1;
				}
	}

	int num_zeroes = 0;
	int num_ones = 0;
	int num_twos = 0;
	int num_threes = 0;
	int num_greater = 0;

	for (int j = 0; j < numCells; j++) 
	{
		if (counts[j] == 0)
			num_zeroes += 1;
		if (counts[j] == 1)
			num_ones += 1;
		if (counts[j] == 2)
			num_twos += 1;
		if (counts[j] == 3)
			num_threes += 1;
		if (counts[j] > 3)
			num_greater += 1;
	}
	std::cout << "nx: " << nx << ", ny: " << ny << ", nz: " << nz << std::endl;
	std::cout << "num_cells =" <<  numCells << std::endl;
	std::cout << "numZeroes = " << num_zeroes << "  numOnes = " << num_ones << "  numTwos = " << num_twos << std::endl;
	std::cout << "numThrees = " << num_threes << "  numGreater = " << num_greater << std::endl;
}
