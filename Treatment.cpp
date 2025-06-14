#include "Treatment.h"
#include "Resource.h"
Treatment::Treatment(int d)
{
	duration = d;
	AssignmentTime = -1;
	AssignedResource = nullptr;
}

Treatment::~Treatment()
{
	AssignedResource = nullptr;
}

void Treatment::setAssignmentTime(int AT)
{
	AssignmentTime = AT;
}

void Treatment::AssignResource(Resource* r)
{
	AssignedResource = r;
}

bool Treatment::isFinished(int current) const
{
	return (current >= (AssignmentTime + duration));
}

string Treatment::GetResourceData()
{
	return (AssignedResource->GetType() + to_string(AssignedResource->GetID()));
}

int Treatment::GetDuration() const
{
	return duration;
}

