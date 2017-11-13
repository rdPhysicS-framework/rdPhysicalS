#include "ToRest.h"
#include "..\..\base\Collaborator.h"

USING_RDPS
USING_PDCT

State<Collaborator> *ToRest::INSTANCE = nullptr;

ToRest::ToRest()
{}

ToRest::~ToRest()
{}

State<Collaborator>* ToRest::Get()
{
	if (!INSTANCE)
		INSTANCE = new ToRest();
	return INSTANCE;
}

void ToRest::Enter(const Collaborator &c)
{
}

void ToRest::Execute(const Collaborator &c)
{
}

void ToRest::Exit(const Collaborator &c)
{
}

bool ToRest::OnMessage(const Collaborator &c, const Message & msg)
{
	return false;
}
