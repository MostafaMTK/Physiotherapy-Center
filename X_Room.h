#pragma once
#include "Resource.h"
class X_Room : public Resource
{
private:
	int Capacity;
	int CurrentNumberOfPatients;
	static int Count;
public:
	X_Room(int c);
	bool AddPatient();
	bool RemovePatient();
	int getCapacity() const;
	int getCurrentNumberOfPatients() const;
};


