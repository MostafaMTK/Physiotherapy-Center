#pragma once
#include "Treatment.h"
class Scheduler;
class Patient;
class E_Therapy : public Treatment
{
public:
	E_Therapy(int d);
	virtual bool canAssign(Scheduler* scheduler);
	virtual void moveToWait(Scheduler* scheduler, Patient* p);
	virtual void returnDevice(Scheduler* scheduler);
	virtual int GetListLatency(Scheduler*);
};

