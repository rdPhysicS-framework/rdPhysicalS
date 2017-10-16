#include "LoaderFiles.h"
#include <vector>
#include <ostream>
#include <sstream>
#include <fstream>

std::string rdps::Cl::LoaderFiles::LoadSource(std::initializer_list<std::string> files)
{
	/*verifica se a lista � nula. se for lan�a um exce��o*/
	if (files.size() == 0)
		throw std::exception("You must provide kernel names!");

	std::string code;
	/*captura o array de endere�os*/
	std::vector<std::string> f = files;

	/*agrupa os conteudos de cada arquivo*/
	for (std::string i : f)
		code += ReadInputStream(i);

	return code;
}

std::string rdps::Cl::LoaderFiles::ReadInputStream(std::string name)
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
		throw std::out_of_range(e.what());
	}

	return code;
}
