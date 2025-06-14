#include "EU_WaitList.h"
#include "Patient.h"
EU_WaitList::EU_WaitList()
{
	Ttime = 0;
}

void EU_WaitList::insertSorted(Patient*& newPatient)
{
	if (!newPatient) return;
	Node<Patient*>* Ptr = new Node<Patient*>(newPatient);
	Ttime += newPatient->GetTreatmentDuration();
	count++;
	if (isEmpty())
	{
		frontPtr = Ptr;
		backPtr = Ptr;
		return;
	}
	Node<Patient*>* FPtr = frontPtr->getNext();
	Node<Patient*>* prev = frontPtr;
	if ((newPatient->GetPT() + newPatient->GetPenality()) < (frontPtr->getItem()->GetPT() + frontPtr->getItem()->GetPenality()))
	{
		Ptr->setNext(frontPtr);
		frontPtr = Ptr;
	}
	else if ((newPatient->GetPT() + newPatient->GetPenality()) >= (backPtr->getItem()->GetPT() + backPtr->getItem()->GetPenality()))
	{
		backPtr->setNext(Ptr);
		backPtr = Ptr;
	}
	else while (FPtr)
	{
		if ((newPatient->GetPT() + newPatient->GetPenality()) < (FPtr->getItem()->GetPT() + FPtr->getItem()->GetPenality()))
		{
			Ptr->setNext(FPtr);
			prev->setNext(Ptr);
			FPtr = FPtr->getNext();
			return;
		}
		prev = prev->getNext();
		FPtr = FPtr->getNext();
	}
}

bool EU_WaitList::enqueue(Patient*& newPatient)
{
	if (!newPatient) return false ;
	Ttime += newPatient->GetTreatmentDuration();
	return LinkedQueue::enqueue(newPatient);
}

bool EU_WaitList::dequeue(Patient*& frntEntry)
{
	if (LinkedQueue::dequeue(frntEntry))
	{
		Ttime -= frntEntry->GetTreatmentDuration();
		return true;
	}
	return false;
}

int EU_WaitList::calcTreatmentLatency() const
{
	return Ttime;
}

