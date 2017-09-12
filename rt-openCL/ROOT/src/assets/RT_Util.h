#ifndef	__RT_UTIL_H__
#define	__RT_UTIL_H__

#include <iostream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <vector>

namespace RT
{
	std::string readInputStream(const std::string &name)
	{
		std::string code;
		std::ifstream kernelFile;

		kernelFile.exceptions(std::ifstream::failbit |
			std::ifstream::badbit);

		try
		{
			kernelFile.open(name.c_str());

			std::stringstream kernelStream;

			kernelStream << kernelFile.rdbuf();

			kernelFile.close();

			code = kernelStream.str();
		}
		catch (std::ifstream::failure &e)
		{
			throw std::out_of_range(e.what());
		}

		return code;
	}

	std::string LoadSource(std::initializer_list<std::string> kernels)
	{
		if (kernels.size() == 0)
		{
			throw std::exception("You must provide kernel names!");
		}

		std::string code;
		std::vector<std::string> k = kernels;
		for (std::string i : k)
		{
			code += readInputStream(i);
		}

		return code;
	}
}

#endif//__RT_UTIL_H__ 