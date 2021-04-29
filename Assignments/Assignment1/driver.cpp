#include <iostream>
#include <string>
#include "tlist.h"

using namespace std;

template <typename T>
void PrintList(const TList<T>& L, string label)
{
    cout << label << " size is: " << L.GetSize() << "\n"
         << label << " = ";
    L.Print(cout);
    cout << "\n\n";
}

int main()
{
    TList<int> L1;		// integer list

    for (int i = 0; i < 10; i++)
        L1.InsertBack(i*2);

    PrintList(L1, "L1");

    for (int i = 0; i < 8; i++)
        L1.InsertFront( (i+1) * 100 );

    PrintList(L1, "L1");

    L1.RemoveBack();
    PrintList(L1, "L1");

    L1.RemoveBack();
    PrintList(L1, "L1");

    L1.RemoveFront();
    PrintList(L1, "L1");

    L1.RemoveFront();
    PrintList(L1, "L1");

    // try an iterator, and some middle inserts/deletes
    cout << "Testing some inserts with an iterator\n\n";

    TListIterator<int> itr = L1.GetIterator();
    L1.Insert(itr, 999);
    itr.Next();
    itr.Next();				// advance two spots
    L1.Insert(itr, 888);
    itr.Next();
    itr.Next();
    itr.Next();				// advance three spots
    L1.Insert(itr, 777);

    PrintList(L1, "L1");

    cout << "Testing some removes (with iterator)\n\n";

    itr.Next();
    itr.Next();   			// advance two spots
    itr = L1.Remove(itr);		// delete current item
    PrintList(L1, "L1");

    for (int i = 0; i < 5; i++)
        itr.Previous();			// back 5 spots

    itr = L1.Remove(itr);		// delete current item
    PrintList(L1, "L1");

    // building another list

    TList<int> L2;
    for (int i = 0; i < 10; i++)
        L2.InsertBack(i * 3 + 1);

    PrintList(L2, "L2");

    // Testing + overload:
    TList<int> L3 = L1 + TList<int>(100, 7);

    TList<int> L4;
    L4 = L2 + L1;

    PrintList(L3, "L3");
    PrintList(L4, "L4");

}