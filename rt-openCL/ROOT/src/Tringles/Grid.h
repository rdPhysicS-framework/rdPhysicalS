#ifndef	 __RDPHS_GRID_H__
#define	 __RDPHS_GRID_H__

#include <map>
#include "..\assets\Config.h"

namespace rdPhs 
{
	class Grid 
	{
	private:
		int nx, ny, nz;
		RT_BBox bbox;
		std::map<int, std::vector<int>> cells;
		bool reverseNormal;

		/*temp*/
		std::vector<RT_Primitive> *objects;

		RT::Vec3f FindMinBounds();
		RT::Vec3f FindMaxBounds();

	public:
		Grid(std::vector<RT_Primitive> *objects);
		~Grid();

		void SetupCells();
	};
}

#endif //__RDPHS_GRID_H__