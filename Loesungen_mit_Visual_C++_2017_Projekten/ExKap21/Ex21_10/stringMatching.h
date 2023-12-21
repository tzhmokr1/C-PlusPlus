// -----------------------------------------------------------
// stringMatching.h
// Definiert die Klasse StringMatching.
// -----------------------------------------------------------
#ifndef _STRINGMATCHING_
#define _STRINGMATCHING_

#include <string>
using namespace std;

class StringMatching
{
  private:
    string pattern;         // Suchstring
    int *deltaTable;        // Entfernungstabelle

  public:
    StringMatching( const string& pat);
    ~StringMatching() { delete [] deltaTable; }

    void print() const;  
};

#endif   // _STRINGMATCHING_