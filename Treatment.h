#pragma once
#include "string"
using namespace std;
class Scheduler;
class Resource;
class Patient;
class Treatment
{
protected:
	int duration;
	int AssignmentTime;
	Resource* AssignedResource;
public:
	Treatment(int d);
	~Treatment();
	void setAssignmentTime(int AT);
	virtual bool canAssign(Scheduler*) = 0;
	virtual void moveToWait(Scheduler*, Patient* p) = 0;
	virtual void returnDevice(Scheduler*) = 0;
	virtual int GetListLatency(Scheduler*) = 0;
	void AssignResource(Resource* r);
	bool isFinished(int current) const;
	string GetResourceData();
	int GetDuration() const;

};

