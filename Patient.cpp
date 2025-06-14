#include "Patient.h"
#include"Treatment.h"
#include "Scheduler.h"
int Patient::Count = 0;
Patient::Patient(int pt, int vt, LinkedQueue<Treatment*>* Req_T, char t)
{
	Treatment* treat;
	ID = ++Count;
	PT = pt;
	VT = vt;
	TT = 0;
	FT = -1;
	type = t;
	Penalty = (VT > PT) ? (VT - PT) / 2 : 0;
	PState = NotArrived;
	canceled = false;
	rescheduled = false;
	while (Req_T->dequeue(treat))
	{
		Req_TreatmentsList.enqueue(treat);
	}
}


Patient::~Patient()
{
	Treatment* treat;
	while (Req_TreatmentsList.dequeue(treat)) delete treat;
}


bool Patient::checkPatient(int curtime, Scheduler* scheduler) const
{
	if (PState == NotArrived)
	{
		//Logic Here
		if (VT <= curtime)
			return true;
		return false;
	}
	if (PState == Early)
	{
		//Logic Here
		if (PT <= curtime)
			return true;
		return false;
	}
	if (PState == Late)
	{
		//Logic Here
		if ((VT + Penalty) <= curtime)
			return true;
		return false;
	}
	if (PState == InTreatment)
	{
		//Logic Here
		Treatment* treat;
		if (Req_TreatmentsList.peek(treat))
			if (treat->isFinished(curtime))
				return true;
		return false;
	}
	if (PState == Waiting)
	{
		//Logic Here
		Treatment* treat;
		if (Req_TreatmentsList.peek(treat))
			if (treat->canAssign(scheduler))
				return true;
		return false;
	}
	return true;
}

int Patient::GetTreatmentDuration() const
{
	Treatment* treat;
	if (Req_TreatmentsList.peek(treat))
		return treat->GetDuration();
	return 0;
}

int Patient::GetTotalWaitingTime()const
{
	return(FT - VT - TT);
}
void Patient::RearangeRPTList(Scheduler* sch)
{
	if (type == 'N')
		return;
	Treatment* treat =NULL;
	Treatment* min = NULL;
	LinkedQueue<Treatment*> temp;
	int mint;
	int late;
	if (Req_TreatmentsList.dequeue(treat))
	{
		mint = treat->GetListLatency(sch);
		min = treat;
	}
	while (Req_TreatmentsList.dequeue(treat))
	{
		late = treat->GetListLatency(sch);
		if (late < mint)
		{
			temp.enqueue(min);
			mint = late;
			min = treat;
		}
		else
			temp.enqueue(treat);
	}
	if(min)
	Req_TreatmentsList.enqueue(min);
	while (temp.dequeue(treat))
		Req_TreatmentsList.enqueue(treat);
}

void Patient::SetFT(int ft)
{
	FT = ft;
}

int Patient::GetFT()const
{
	return FT;
}

bool Patient::Cancel(int &x)
{
	if (Req_TreatmentsList.GetCount() > 1)
		return false;
	canceled = true;
	Treatment* treat;
	Req_TreatmentsList.dequeue(treat);
	x = treat->GetDuration();
	delete treat;
	return true;
}

void Patient::Resc(int newpt)
{
	PT = newpt;
	rescheduled = true;
}


void Patient::IncreaseTT(int time)
{
	TT += time;
}

void Patient::SetPState(Patient_State p)
{
	PState = p;
}

Patient_State Patient::GetState() const
{
	return PState;
}

int Patient::GetPT() const
{
	return PT;
}

int Patient::GetPenality() const
{
	return Penalty;
}

int Patient::GetVT() const
{
	return VT;
}

string Patient::GetAssignedResourceData() const
{
	Treatment* treat;
	Req_TreatmentsList.peek(treat);
	return treat->GetResourceData();
}

int Patient::getID() const
{
	return ID;
}

char Patient::getType() const
{
	return type;
}

int Patient::getTT() const
{
	return TT;
}

bool Patient::isCanceled() const
{
	return canceled;
}

bool Patient::isResc() const
{
	return rescheduled;
}

Treatment* Patient::FinishTreatment()
{
	Treatment* treat;
	Req_TreatmentsList.dequeue(treat);
	return treat;
}

Treatment* Patient::NextTreatment()
{
	Treatment* treat = NULL;
	Req_TreatmentsList.peek(treat);
	return treat;
}

ostream& operator<<(ostream& o, Patient* p)
{
	if (p->PState == NotArrived)
	{
		o << "P" << p->ID << "_" << p->VT;
	}
	else if (p->PState == InTreatment) // use function get resource data in the treatment class
	{
		o << "P" << p->ID << "_" << p->GetAssignedResourceData();
	}
	else
	{
		o << p->ID;
	}
	return o;
}