#include "X_Therapy.h"
#include "Scheduler.h"
#include "Patient.h"

X_Therapy::X_Therapy(int d) :Treatment(d)
{
}

bool X_Therapy::canAssign(Scheduler* scheduler)
{
	return scheduler->isAvailableX_Room();
}

void X_Therapy::moveToWait(Scheduler* scheduler, Patient* p)
{
	scheduler->moveToX_Waiting(p);
}

void X_Therapy::returnDevice(Scheduler* scheduler)
{
	scheduler->retrieveX_Room(AssignedResource);
	AssignedResource = nullptr;
}

int X_Therapy::GetListLatency(Scheduler* scheduler)
{
	return scheduler->getX_Latency();
}
