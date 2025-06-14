#pragma once
#include "PriQueue.h"
class Patient;
class EarlyPList : public PriQueue<Patient*>
{
private:

public:
	bool reschedule(int Presc );
};