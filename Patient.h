#pragma once
#include <iostream>
#include "LinkedQueue.h"
#include "EarlyPList.h"
class Scheduler;
class Treatment;
using namespace std;
enum Patient_State
{
	NotArrived,
	Early,
	Late,
	Waiting,
	InTreatment,
	Finished
};
class Patient
{
private:
	int VT, TT, PT, ID, Penalty, FT;
	char type;
	LinkedQueue<Treatment*>Req_TreatmentsList;
	Patient_State PState;
	bool canceled, rescheduled;
	static int Count;
public:
	Patient(int pt, int vt, LinkedQueue<Treatment*>* Req_T, char t);
	~Patient();
	friend ostream& operator <<(ostream&, Patient*);
	bool checkPatient(int , Scheduler* ) const;
	void SetFT(int );
	int GetFT()const;
	int GetTreatmentDuration()const;
	int GetTotalWaitingTime()const;
	void RearangeRPTList(Scheduler* sch);
	bool Cancel(int &x);
	void Resc(int newpt);
	void IncreaseTT(int time);
	void SetPState(Patient_State p);
	Patient_State GetState() const;
	int GetPT() const;
	int GetPenality() const;
	int GetVT() const;
	string GetAssignedResourceData() const;
	int getID() const;
	char getType() const;
	int getTT() const;
	bool isCanceled() const;
	bool isResc() const;
	Treatment* FinishTreatment();
	Treatment* NextTreatment();
};