#ifndef	__VIEW_PLANE_H__
#define	__VIEW_PLANE_H__

#include "..\..\GlobalDefs.h"
#include <RTmath.h>

RDPS_BEGIN
	FRWK_BEGIN

		class ViewPlane
		{
		private:
			int width;
			int height;
			RT::Vec2f sp;

			//int numSamples;

		public:
			ViewPlane(const int _width, 
					  const int _height);
			~ViewPlane();

			inline int GetWidth()			const { return width;  }
			inline int GetHeight()			const { return height; }
			inline RT::Vec2f GetSizePixel() const { return sp;     }
		};

	FRWK_END
RDPS_END

#endif//__VIEW_PLANE_H__