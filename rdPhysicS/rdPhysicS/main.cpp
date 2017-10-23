#include <iostream>
#include "src\rdps-CL\Util\LogError.h"
#include "src\rdps-CL\Application\ApplicationCLFactor.h"
#include "src\rdps-CL\Application\ApplicationCL.h"
#include "src\rdps-packages\ArrayBuffer.h"
#include <SDL.h>
#include "src\rdps-CL\ClGlobalDef.h"
#include "src\rdps-packages\input\Package.h"
#include "src\rdps-packages\input\Container.h"
#include "src\rdps-packages\input\ContainerBuilder.h"
#include "src\rdps-packages\output\FinalProduct.h"
#include "src\World.h"

USING_RDPS
USING_CL
USING_PKG

int main(int argc, char **argv)
{
	try
	{
		WORLD_GET->Set(ApplicationCLFactor::CreateApplicationUsersInput());
		FinalProduct<char> f(20);
		WORLD_GET_APP->Process(true);
		f.ApplyBuffer();

		std::cout << "id: " << f.GetBuffer()->GetId() << "\nelement: " << f.GetData() << std::endl;
	}
	catch (const LogError &e)
	{
		std::cout << e.what() << std::endl;
	}

	system("pause");
	return 0;
}