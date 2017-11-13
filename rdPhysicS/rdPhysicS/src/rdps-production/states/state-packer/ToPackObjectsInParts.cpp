#include "ToPackObjectsInParts.h"
#include "..\..\collaborators\PackerObjects.h"

USING_RDPS
USING_PDCT

State<PackerObjects> *ToPackObjectsInParts::INSTANCE = nullptr;

ToPackObjectsInParts::ToPackObjectsInParts()
{}

ToPackObjectsInParts::~ToPackObjectsInParts()
{}

State<PackerObjects> *ToPackObjectsInParts::Get()
{
	if (!INSTANCE)
		INSTANCE = new ToPackObjectsInParts();
	return INSTANCE;
}

void ToPackObjectsInParts::Enter(const PackerObjects &c)
{
}

void ToPackObjectsInParts::Execute(const PackerObjects &c)
{
}

void ToPackObjectsInParts::Exit(const PackerObjects &c)
{
}

bool ToPackObjectsInParts::OnMessage(const PackerObjects &c, const Message &msg)
{
	return false;
}
