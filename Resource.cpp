#include "Resource.h"
#include "X_Room.h"
Resource::Resource(char t, int id) :ID(id), Type(t)
{
	Type = t;
}

Resource::~Resource()
{
}

int Resource::GetID() const
{
	return ID;
}

char Resource::GetType() const
{
	return Type;
}

ostream& operator<< (ostream& o, Resource* r)
{

	if (X_Room* x = dynamic_cast<X_Room*>(r))
		o << "R" << x->ID << "[" << x->getCurrentNumberOfPatients() << ", " << x->getCapacity() << "]";
	else
		o << r->ID;
	return o;
}
