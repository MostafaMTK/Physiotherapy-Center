#include "X_WaitList.h"
#include "Patient.h"

bool X_WaitList::cancel(int Pcancel, Patient*& p)
{
    p = NULL;
    int random = rand() % 101;
    if (random < Pcancel && count > 0)
    {
        Patient* curr;
        int rPatient = rand() % count;
        int x;
        if (rPatient == 0)
        {
            peek(curr);
            if (curr->Cancel(x))
            {
                Node<Patient*>* ptr = frontPtr;
                frontPtr = frontPtr->getNext();
                if (!frontPtr) backPtr = NULL;
                Ttime -= x;
                count--;
                p = curr;
                return true;
            }
            else
            {
                return false;
            }
        }
        rPatient--;
        Node <Patient*>* prev = frontPtr;
        Node <Patient*>* ptr = frontPtr->getNext();

        while (rPatient)
        {
            prev = prev->getNext();
            ptr = ptr->getNext();
            rPatient--;
        }
        curr = ptr->getItem();
        if (curr->Cancel(x))
        {
            prev->setNext(ptr->getNext());
            count--;
            Ttime -= x;
            if (prev->getNext() == NULL) backPtr = prev;
            p = curr;
            return true;
        }
    }
    return false;
}
