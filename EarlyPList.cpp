#include "EarlyPList.h"
#include "Patient.h"
bool EarlyPList::reschedule(int Presc)
{
    int random = rand() % 101;
    int rpt = rand() % 21;
    if (random < Presc && count>0)
    {
        int pri;
        Patient* curr;
        int rPatient = rand() % count;

        if (rPatient == 0 && !head->getItem(pri)->isResc())
        {
            dequeue(curr, pri);
            curr->Resc(-pri + rpt);
            enqueue(curr, -curr->GetPT());
            return true;
        }
        if (!rPatient) return false;
        rPatient--;
        PriNode <Patient*>* prev = head;
        PriNode <Patient*>* ptr = head->getNext();

        while (rPatient--)
        {
            prev = prev->getNext();
            ptr = ptr->getNext();
        }
        curr = ptr->getItem(pri);
        if (!curr->isResc())
        {
            prev->setNext(ptr->getNext());
            ptr->setNext(NULL);
            delete ptr;
            count--;
            curr->Resc(-pri + rpt);
            enqueue(curr, -curr->GetPT());
            return true;
        }
    }
    return false;
}