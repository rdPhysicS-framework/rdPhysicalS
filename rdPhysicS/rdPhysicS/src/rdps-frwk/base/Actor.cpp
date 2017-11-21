#include "Actor.h"
#include "..\Util\Transform.h"

USING_RDPS
USING_FRWK

Actor::Actor() :
	   transform(new Transform),
	   tag()
{}

//Actor::Actor(Transform *_transform) :
//	   transform(_transform),
//	   tag()
//{}

/*Actor::Actor(const RT::Vec3f &position, 
			 const RT::Vec3f &rotation, 
			 const RT::Vec3f &scale) :
	   transform(new Transform(position, 
							   rotation, 
						       scale))
{}*/

/*Actor::Actor(const RT::Vec3f &position) :
	   transform(new Transform(position))
{}*/

Actor::Actor(const Actor &other) :
	   transform(other.transform->Clone()),
	   tag(other.tag)
{}

Actor::~Actor()
{
	if (transform)
		delete transform;
}

Actor *Actor::Clone() const
{
	return new Actor(*this);
}

Actor &Actor::operator=(const Actor &other)
{
	*transform = *other.transform;
	tag = other.tag;
	return (*this);
}

Transform *Actor::GetTransform() const
{
	return transform;
}

const std::string &Actor::GetTag() const
{
	return tag;
}

Actor &Actor::SetTansform(const Transform &_transform)
{
	*transform = _transform;
	return (*this);
}

Actor &Actor::SetTag(const std::string _tag)
{
	tag = _tag;
	return (*this);
}
