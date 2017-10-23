#include "LoaderFiles.h"
#include "LogError.h"
#include <vector>
#include <ostream>
#include <sstream>
#include <fstream>

USING_RDPS
USING_CL

std::string LoaderFiles::LoadSource(std::initializer_list<std::string> files)
{
	/*verifica se a lista é nula. se for lança um exceção*/
	if (files.size() == 0)
		Logger::Log("You must provide kernel names!");

	std::string code;
	/*captura o array de endereços*/
	std::vector<std::string> f = files;

	/*agrupa os conteudos de cada arquivo*/
	for (std::string i : f)
		code += ReadInputStream(i);

	return code;
}

std::string LoaderFiles::ReadInputStream(std::string name)
{
	std::string code;
	std::ifstream fileKernel;

	fileKernel.exceptions(std::ifstream::failbit |
						  std::ifstream::badbit);

	try
	{
		fileKernel.open(name.c_str());

		std::stringstream stream;
		stream << fileKernel.rdbuf();

		fileKernel.close();

		code = stream.str();
	}
	catch (std::ifstream::failure &e)
	{
		Logger::Log(e.what());
	}

	return code;
}
