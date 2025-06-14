#include "E_Therapy.h"
#include "Scheduler.h"
#include "Patient.h"
E_Therapy::E_Therapy(int d) : Treatment(d)
{
}
bool E_Therapy::canAssign(Scheduler* scheduler)
{
	return scheduler->isAvailableE_Device();
}

void E_Therapy::moveToWait(Scheduler* scheduler, Patient* p)
{
	scheduler->moveToE_Waiting(p);
}

void E_Therapy::returnDevice(Scheduler* scheduler)
{
	scheduler->retrieveE_Device(AssignedResource);
	AssignedResource = nullptr;
}

int E_Therapy::GetListLatency(Scheduler* scheduler)
{
	return scheduler->getE_Latency();
}
