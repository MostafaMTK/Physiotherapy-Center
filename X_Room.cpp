#include "X_Room.h"

int X_Room::Count = 0;


X_Room::X_Room(int c) :Resource('X', ++Count)
{
	Capacity = c;
	CurrentNumberOfPatients = 0;
}

bool X_Room::AddPatient()
{
	if (++CurrentNumberOfPatients == Capacity)
		return true;
	return false;
}

bool X_Room::RemovePatient()
{
	if (--CurrentNumberOfPatients == Capacity - 1)
	{
		return true;
	}
	return false;
}

int X_Room::getCapacity() const
{
	return Capacity;
}

int X_Room::getCurrentNumberOfPatients() const
{
	return CurrentNumberOfPatients;
}
