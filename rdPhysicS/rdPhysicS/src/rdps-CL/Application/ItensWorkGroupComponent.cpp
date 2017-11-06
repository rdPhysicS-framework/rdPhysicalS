#include "ItensWorkGroupComponent.h"
#include "..\..\Util\LogError.h"
#include <string>

USING_RDPS
USING_CL

ItensWorkGroupComponent::ItensWorkGroupComponent(const std::initializer_list<size_t> gItemSize , 
												   const std::initializer_list<size_t> lwItemSize,
												   const std::initializer_list<size_t> _offSet    ) :
	      globalItemSize(gItemSize),
		  localWorkItemSize(lwItemSize),
		  offSet(_offSet)
{}

ItensWorkGroupComponent::~ItensWorkGroupComponent()
{
	globalItemSize.clear();
	localWorkItemSize.clear();
	offSet.clear();
}

const cl_uint ItensWorkGroupComponent::GetDimensions() const
{
	cl_uint size = static_cast<cl_uint>(globalItemSize.size());
	if(size == 0 && size > 3)
		Logger::Log("ERROR numbers of incorrect indexes of "
					"items of works. (min 1 max 3).\n Input size: "
					+ std::to_string(size));
	return size;
			
}
