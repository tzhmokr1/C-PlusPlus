// ---------------------------------------------------------
// ex21_12.cpp
// Verwendet ein Objekt der Klasse StringMatching.
// ---------------------------------------------------------
#include "stringMatching.h"
#include <iostream>
using namespace std;

int main()
{
    StringMatching strMatching("is as easy as");
    strMatching.print();

    int pos = strMatching.findIn("Nothing is as easy as it looks\n");
    if( pos >= 0)
        cout << "Position des Suchstrings: " << pos+1 << endl;

    return 0;
}