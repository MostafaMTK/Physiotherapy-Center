#include "U_Therapy.h"
#include "Scheduler.h"
#include "Patient.h"

U_Therapy::U_Therapy(int d) : Treatment(d)
{
}

bool U_Therapy::canAssign(Scheduler* scheduler)
{
	return scheduler->isAvailableU_Device();
}

void U_Therapy::moveToWait(Scheduler* scheduler, Patient* p)
{
	scheduler->moveToU_Waiting(p);
}

void U_Therapy::returnDevice(Scheduler* scheduler)
{
	scheduler->retrieveU_Device(AssignedResource);
	AssignedResource = nullptr;
}

int U_Therapy::GetListLatency(Scheduler* scheduler)
{
	return scheduler->getU_Latency();
}
