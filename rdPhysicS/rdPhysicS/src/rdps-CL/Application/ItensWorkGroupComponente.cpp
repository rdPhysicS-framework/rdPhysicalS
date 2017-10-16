#include "ItensWorkGroupComponente.h"
#include <string>

USING_RDPS
USING_CL

ItensWorkGroupComponente::ItensWorkGroupComponente(const std::initializer_list<size_t> gItemSize , 
												   const std::initializer_list<size_t> lwItemSize,
												   const std::initializer_list<size_t> _offSet    ) :
	      globalItemSize(gItemSize),
		  localWorkItemSize(lwItemSize),
		  offSet(_offSet)
{}

const size_t ItensWorkGroupComponente::GetDimensions() const
{
	int size = globalItemSize.size();
	return (size > 0 && size <= 3) ? size :
			throw std::out_of_range("ERROR numbers of incorrect indexes of "
								    "items of works. (min 1 max 3).\n Input size: " 
									+ std::to_string(size));
}
