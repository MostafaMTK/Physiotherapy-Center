#include "Scheduler.h"
#include "Patient.h"
#include "Treatment.h"
#include "Resource.h"
#include "E_Device.h"
#include "U_Device.h"
#include "X_Room.h"
#include "E_Therapy.h"
#include "U_Therapy.h"
#include "X_Therapy.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
using namespace std;

Scheduler::Scheduler()
{
	inputfilename = userinterface.getinputfilename();
	interfacemode = userinterface.getinterfacemode();
	CurrentTimeStep = 0;
	NumOfAllPatients = 0;
	NumOfNP = 0;
	NumOfRP = 0;
	NumOfEarlyP = 0;
	NumOfLateP = 0;
	TotalWaitingNP = 0;
	TotalWaitingRP = 0;
	TotalPenalties = 0;
	NumOfCancels = 0;
	NumOfResc = 0;
	importData();
}

int Scheduler::GetCurrentTimeStep() const
{
	return CurrentTimeStep;
}

void Scheduler::moveToE_Waiting(Patient* p)
{
	if (p->GetState() == NotArrived)
		E_WList.enqueue(p);
	else
		E_WList.insertSorted(p);
	p->SetPState(Waiting);
}

void Scheduler::moveToU_Waiting(Patient* p)
{
	if (p->GetState() == NotArrived)
		U_WList.enqueue(p);
	else
		U_WList.insertSorted(p);
	p->SetPState(Waiting);
}

void Scheduler::moveToX_Waiting(Patient* p)
{
	if (p->GetState() == NotArrived)
		X_WList.enqueue(p);
	else
		X_WList.insertSorted(p);
	p->SetPState(Waiting);
}

Patient* Scheduler::getNextE_Patient()
{
	Patient* p;
	E_WList.peek(p);
	return p;
}

Patient* Scheduler::getNextU_Patient()
{
	Patient* p;
	U_WList.peek(p);
	return p;
}

Patient* Scheduler::getNextX_Patient()
{
	Patient* p;
	X_WList.peek(p);
	return p;
}

Patient* Scheduler::getNextALL_Patient()
{
	Patient* p;
	AllPatients.peek(p);
	return p;
}

Resource* Scheduler::getE_Device()
{
	Resource* r;
	E_Devices.dequeue(r);
	return r;
}

Resource* Scheduler::getU_Device()
{
	Resource* r;
	U_Devices.dequeue(r);
	return r;
}

Resource* Scheduler::getX_Room()
{
	Resource* r;
	X_Rooms.peek(r);
	X_Room* x = dynamic_cast<X_Room*>(r);
	if (x->AddPatient())
		X_Rooms.dequeue(r);
	return r;
}

void Scheduler::retrieveE_Device(Resource* r)
{
	E_Devices.enqueue(r);
}

void Scheduler::retrieveU_Device(Resource* r)
{
	U_Devices.enqueue(r);
}

void Scheduler::retrieveX_Room(Resource* r)
{
	X_Room* x = dynamic_cast<X_Room*>(r);
	if (x->RemovePatient())
		X_Rooms.enqueue(r);
}

void Scheduler::moveToEarlyPatients(Patient* p)
{
	p->SetPState(Early);
	EarlyPatients.enqueue(p, -p->GetPT());
}

void Scheduler::moveToLatePatients(Patient* p)
{
	p->SetPState(Late);
	LatePatients.enqueue(p, -(p->GetPT() + p->GetPenality()));
}

void Scheduler::moveToInTreatmentPatients(Patient* p)
{
	p->SetPState(InTreatment);
	InTreatmentPatients.enqueue(p, -(p->GetTreatmentDuration() + CurrentTimeStep));
}



void Scheduler::moveToFinishedPatients(Patient* p)
{
	p->SetPState(Finished);
	FinishedPatients.push(p);
}

bool Scheduler::isAvailableE_Device()
{
	return (E_Devices.GetCount()!=0);
}

bool Scheduler::isAvailableU_Device()
{
	return (U_Devices.GetCount()!=0);
}

bool Scheduler::isAvailableX_Room()
{
	return (X_Rooms.GetCount()!=0);
}

int Scheduler::getE_Latency()
{
	return E_WList.calcTreatmentLatency();
}

int Scheduler::getU_Latency()
{
	return U_WList.calcTreatmentLatency();
}

int Scheduler::getX_Latency() 
{
	return X_WList.calcTreatmentLatency();
}

void Scheduler::importData()
{
	ifstream in;
	in.open("Data\\Input Files\\" + inputfilename + ".txt");
	in >> NE >> NU >> NG;
	Resource* tempresource;
	for(int i = 0 ; i < NE ; i++)
	{
		tempresource = new E_Device;
		E_Devices.enqueue(tempresource);
	}
	for(int i = 0 ; i < NU; i ++)
	{
		tempresource = new U_Device;
		U_Devices.enqueue(tempresource);
	}
	int cap;
	for(int i = 0 ; i < NG; i++)
	{
		in >> cap;
		tempresource = new X_Room(cap);
		X_Rooms.enqueue(tempresource);
	}
	in >> PCancel >> PResc;
	in >> NumOfAllPatients;
	char type;
	int pt, vt, nt;
	LinkedQueue<Treatment*> tempQ;
	Treatment* tempT;
	char Ttype;
	int Td;
	Patient* p;
	for (int i = 0; i < NumOfAllPatients; i++)
	{
		in >> type >> pt >> vt >> nt;
		while (nt--)
		{
			in >> Ttype >> Td;
			if (Ttype == 'E' || Ttype == 'e')
				tempT = new E_Therapy(Td);
			else if (Ttype == 'U' || Ttype == 'u')
				tempT = new U_Therapy(Td);
			else if (Ttype == 'X' || Ttype == 'x')
				tempT = new X_Therapy(Td);
			tempQ.enqueue(tempT);
		}
		p = new Patient(pt, vt, &tempQ, type);
		AllPatients.enqueue(p);
	}
	in.close();
	cout << "Data Has Been Imported Successfully\n";
}

void Scheduler::exportData()
{
	ofstream out;
	outputfilename = userinterface.getoutputfilename();
	out.open("Data\\Output Files\\" + outputfilename + ".txt");
	out << "PID" << "	" << "PType" << "	" << "PT" << "	" << "VT" << "	" << "FT" << "	" << "WT" << "	" << "TT" << "	" << "Cancel" << "	" << "Resc\n";
	ArrayStack<Patient*> temp;
	Patient* p;
	while (FinishedPatients.pop(p))
	{
		temp.push(p);
		out << left << setw(3) << ("P" + to_string(p->getID())) << "	";
		out << left << setw(5) << p->getType() << "	";
		out << left << setw(2) << p->GetPT() << "	";
		out << left << setw(2) << p->GetVT() << "	";
		out << left << setw(2) << p->GetFT() << "	";
		out << left << setw(2) << p->GetTotalWaitingTime() << "	";
		out << left << setw(2) << p->getTT() << "	";
		out << left << setw(5) << (p->isCanceled() ? "T" : "F") << "	";
		out << left << setw(5) << (p->isResc() ? "T" : "F");
		out << "\n";
	}
	while (temp.pop(p)) FinishedPatients.push(p);
	out << "\nTotal number of timesteps = " << CurrentTimeStep << "\n";
	out << "Total number of all, N, and R patients = " << NumOfAllPatients << ", " << NumOfNP << ", " << NumOfRP << "\n";
	out << "Average total waiting time for all, N, and R patients = " << ((NumOfAllPatients == 0) ? 0 : (float)(TotalWaitingNP + TotalWaitingRP) / NumOfAllPatients) << ", " << ((NumOfNP == 0) ? 0 :(float)TotalWaitingNP / NumOfNP) << ", " << ((NumOfRP == 0) ? 0 :(float)TotalWaitingRP / NumOfRP) << "\n";
	out << "Average total treatment time for all, N, and R patients = " << ((NumOfAllPatients == 0 )? 0 : (float)(TotalTreatmentNP + TotalTreatmentRP) / NumOfAllPatients) << ", " << ((NumOfNP == 0) ? 0 : (float)TotalTreatmentNP / NumOfNP) << ", " << ((NumOfRP == 0) ? 0 : (float)TotalTreatmentRP / NumOfRP) << "\n";
	out << "Percentage of patients of an accepted cancellation (%) = " << ((NumOfAllPatients == 0) ? 0 : (float)100*NumOfCancels/NumOfAllPatients) << " %\n";
	out << "Percentage of patients of an accepted rescheduling (%) = " << ((NumOfAllPatients == 0) ? 0 : (float)100 * NumOfResc / NumOfAllPatients) << " %\n";
	out << "Percentage of early patients (%) = " << ((NumOfAllPatients == 0) ? 0 : (float)100 * NumOfEarlyP / NumOfAllPatients) << " %\n";
	out << "Percentage of late patients (%) = " << ((NumOfAllPatients == 0) ? 0 : (float)100 * NumOfLateP / NumOfAllPatients) << " %\n";
	out << "Average late penalty = " << ((NumOfLateP == 0) ? 0 : (float)TotalPenalties / NumOfLateP) << " timestep(s)\n";
	out.close();
	cout << "Data Has Been Exported Successfully\n";
}

void Scheduler::printDetails(int X) // not yet
{
	userinterface.printDetails(CurrentTimeStep, &E_WList, &U_WList, &X_WList, &E_Devices, &U_Devices, &X_Rooms, &AllPatients, &FinishedPatients, &EarlyPatients,
		&LatePatients, &InTreatmentPatients);
}

void Scheduler::move1TimeStep()
{
	if(FinishedPatients.GetCount() < NumOfAllPatients)
		CurrentTimeStep++;
}

void Scheduler::Simulation()
{
	Patient* p = NULL;
	Treatment* treat = NULL;
	Resource* res = NULL;
	int pt = 0;
	while (FinishedPatients.GetCount() < NumOfAllPatients)
	{
		this->move1TimeStep();
		p = NULL;
		AllPatients.peek(p);
		while (p && p->checkPatient(CurrentTimeStep, this))
		{
			if (p->getType() == 'N' || p->getType() == 'n')
				NumOfNP++;
			else if (p->getType() == 'R' || p->getType() == 'r')
				NumOfRP++;

			AllPatients.dequeue(p);
			if (p->GetVT() > p->GetPT())
			{
				this->moveToLatePatients(p);
				int pen = p->GetPenality();
				TotalPenalties += pen;
				NumOfLateP++;
			}
			else if (p->GetVT() < p->GetPT())
			{
				this->moveToEarlyPatients(p);
				NumOfEarlyP++;
			}
			else
			{
				p->RearangeRPTList(this);
				treat = p->NextTreatment();
				treat->moveToWait(this, p);
			}
			p = NULL;
			AllPatients.peek(p);
		}
		p = NULL;
		EarlyPatients.peek(p, pt);
		while (p && p->checkPatient(CurrentTimeStep, this))
		{
			EarlyPatients.dequeue(p, pt);
			p->RearangeRPTList(this);
			treat = p->NextTreatment();
			treat->moveToWait(this, p);
			p = NULL;
			EarlyPatients.peek(p, pt);
		}
		p = NULL;
		LatePatients.peek(p, pt);
		while (p && p->checkPatient(CurrentTimeStep, this))
		{
			LatePatients.dequeue(p, pt);
			p->RearangeRPTList(this);
			treat = p->NextTreatment();
			treat->moveToWait(this, p);
			p = NULL;
			LatePatients.peek(p, pt);
		}
		p = NULL;
		InTreatmentPatients.peek(p, pt);
		while (p && p->checkPatient(CurrentTimeStep, this))
		{
			InTreatmentPatients.dequeue(p, pt);
			treat = p->FinishTreatment();
			p->IncreaseTT(treat->GetDuration());
			treat->returnDevice(this);
			delete treat;
			treat = NULL;
			p->RearangeRPTList(this);
			treat = p->NextTreatment();
			if (treat)
				treat->moveToWait(this, p);
			else
			{
				moveToFinishedPatients(p);
				if (p->getType() == 'N' || p->getType() == 'n')
				{
					p->SetFT(CurrentTimeStep);
					TotalWaitingNP += p->GetTotalWaitingTime();
					TotalTreatmentNP += p->getTT();
				}
				else if (p->getType() == 'R' || p->getType() == 'r')
				{
					p->SetFT(CurrentTimeStep);
					TotalWaitingRP += p->GetTotalWaitingTime();
					TotalTreatmentRP += p->getTT();
				}
			}
			p = NULL;
			treat = NULL;
			InTreatmentPatients.peek(p, pt);
		}
		p = NULL;
		E_WList.peek(p);
		while (p && p->checkPatient(CurrentTimeStep, this))
		{
			E_WList.dequeue(p);
			treat = NULL;
			treat = p->NextTreatment();
			this->moveToInTreatmentPatients(p);
			res = this->getE_Device();
			treat->AssignResource(res);
			treat->setAssignmentTime(CurrentTimeStep);
			p = NULL;
			E_WList.peek(p);
		}
		p = NULL;
		U_WList.peek(p);
		while (p && p->checkPatient(CurrentTimeStep, this))
		{
			U_WList.dequeue(p);
			treat = NULL;
			treat = p->NextTreatment();
			this->moveToInTreatmentPatients(p);
			res = this->getU_Device();
			treat->AssignResource(res);
			treat->setAssignmentTime(CurrentTimeStep);
			p = NULL;
			U_WList.peek(p);
		}
		p = NULL;
		X_WList.peek(p);
		while (p && p->checkPatient(CurrentTimeStep, this))
		{
			X_WList.dequeue(p);
			treat = NULL;
			treat = p->NextTreatment();
			this->moveToInTreatmentPatients(p);
			res = this->getX_Room();
			treat->AssignResource(res);
			treat->setAssignmentTime(CurrentTimeStep);
			p = NULL;
			X_WList.peek(p);
		}
		p = NULL;
		if (X_WList.cancel(PCancel, p))
		{
			this->moveToFinishedPatients(p);
			NumOfCancels++;
			if (p->getType() == 'N' || p->getType() == 'n')
			{
				p->SetFT(CurrentTimeStep);
				TotalWaitingNP += p->GetTotalWaitingTime();
				TotalTreatmentNP += p->getTT();
			}
			else if (p->getType() == 'R' || p->getType() == 'r')
			{
				p->SetFT(CurrentTimeStep);
				TotalWaitingRP += p->GetTotalWaitingTime();
				TotalTreatmentRP += p->getTT();
			}
		}

		if (EarlyPatients.reschedule(PResc))
			NumOfResc++;
		p = NULL;
		treat = NULL;
		res = NULL;
		if (interfacemode)
			printDetails(pt);
	}
}

Scheduler::~Scheduler()
{
	Patient* p;
	while (FinishedPatients.pop(p)) delete p;
	Resource* r;
	while (E_Devices.dequeue(r)) delete r;
	while (U_Devices.dequeue(r)) delete r;
	while (X_Rooms.dequeue(r)) delete r;
}





