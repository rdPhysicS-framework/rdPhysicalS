#include "ContainerFactory.h"
#include "Package.h"
#include "Container.h"
#include "ContainerBuilder.h"
#include "..\..\Util\LogError.h"
#include "..\object-CL\ObjectsPackage.h"
#include <vector>

USING_RDPS
USING_PKG

Container *ContainerFactory::CreateContainer(std::initializer_list<std::string> _ids, 
											  std::initializer_list<PackageBase*> _pkgs)
{
	size_t size = _pkgs.size();
	if (_ids.size() != size)
		Logger::Log("ERROR when creating the container of packages, the number of"
				    " indexes is different from the number of packages. For to"
					" create the container of packages it is necessary that the"
					" numbers of both are same.\nSize: " + std::to_string(size));

	std::vector<std::string> ids = _ids;
	std::vector<PackageBase*> packages = _pkgs;

	ContainerBuilder cb;

	for (int i = 0; i < size; i++)
	{
		cb.AddPackage(ids[i], packages[i]);
	}

	return cb.Create();
}

Container *ContainerFactory::CreateContainer()
{
	return CreateContainer({ "world", "camera",
							 "lights", "objects" },
							 { new Package<RT_DataScene>(),
							 new Package<RT_Camera>(),
							 new Package<RT_Light>() ,
							 new Package<RT_Primitive>() });
}

//Container *ContainerFactory::CreateTestContainer()
//{
//	return nullptr;
//}
