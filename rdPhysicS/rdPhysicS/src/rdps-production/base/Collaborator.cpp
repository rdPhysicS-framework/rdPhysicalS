#include "Collaborator.h"

USING_RDPS
USING_PDCT

Collaborator::Collaborator(const CollaboratorsFunction _function) :
			  function(_function)
{}

Collaborator::Collaborator(const Collaborator &other) :
			  function(other.function)
{}

bool Collaborator::HandleMessage(const Message &message)
{
	return false;
}
