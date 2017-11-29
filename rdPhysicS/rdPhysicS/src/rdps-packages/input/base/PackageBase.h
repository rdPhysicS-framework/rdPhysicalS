#ifndef	__PACKAGE_BASE_H__
#define	__PACKAGE_BASE_H__

#include "..\..\..\GlobalDefs.h"
#include <vector>

RDPS_BEGIN
	PKG_BEGIN
		/********************************************************************************************************************************************
		 *
		 * Classe Base para os pacotes.
		 * Mesmo os pacotes sendo genericos herdam dessa class,
		 * pois o Container possui uma std::vector de pacotes e sem
		 * essa classe base nao seria possivel ter um array de pacotes
		 * genericos.
		 *
		 ********************************************************************************************************************************************/
		class PackageBase
		{
		public:
			virtual ~PackageBase() {}

			virtual size_t Size() const = 0;
			virtual PackageBase &AddElement(void *_element) = 0;
			virtual PackageBase &AddElements(void *_elements) = 0;
			virtual PackageBase &RemoveElement(const int id) = 0;
			virtual PackageBase &DestroyElements() = 0;
			virtual PackageBase &Update() = 0;
			virtual PackageBase &ToSend() = 0;
			virtual PackageBase &ApplyBuffer() = 0;
		};

	PKG_END
RDPS_END

#endif//__PACKAGE_BASE_H__

