// ---------------------------------------------------------
// myData.cpp
// Implementierung der Methoden der Klasse MyData.
// ---------------------------------------------------------

#include "myData.h"

MyData::MyData() : count(0), iCur(0)
{
   for( int i=0; i < ARR_LENGTH; ++i)
      arrPtrData[i] = NULL;
}

MyData::~MyData() { eraseAll(); }       // Destuktor

MyData::MyData( const MyData& src)      // Kopierkonstruktor
{
   count = 0;    // Kein eraseAll() in nachfolgender Zuweisung.
   *this = src;
}

MyData& MyData::operator=( const MyData& src)  // Zuweisung
{
   if( count > 0)
      eraseAll();               // Zuerst alle Eintr�ge loeschen.
   count = src.count;
   iCur  = src.iCur;
   for( int i=0; i < ARR_LENGTH; ++i)
      if( src.arrPtrData[i] != NULL)
         arrPtrData[i] = src.arrPtrData[i]->clone();
      else 
         arrPtrData[i] = NULL;
   return *this;
}

void MyData::eraseAll()   // Loesch alle Elemente 
{
   if( count == 0)        // Schon leer?
      return; 
   
   for( int i=0; i < ARR_LENGTH; ++i)
      if( arrPtrData[i] != NULL)
      {
         delete arrPtrData[i];
         arrPtrData[i] = NULL;
      }
   count = 0; iCur = 0;
}

bool MyData::erase( double x)
{
   if( count == 0)        // Leer?
      return false; 
   XData *px;
   for( int i=0; i < ARR_LENGTH; ++i)
   {
      px = dynamic_cast<XData*>(arrPtrData[i]);
      if( px != NULL  &&  px->getData() == x )
      {
         delete px;
         arrPtrData[i] = NULL;
         --count;
         return true;
      }
   }
   return false;
}

bool MyData::erase( const char* str)
{
   if( count == 0 || strlen(str) == 0)     // Keine Daten oder 
      return false;                        // leerer String. 
   SData *ps;
   for( int i=0; i < ARR_LENGTH; ++i)
      if( (ps = dynamic_cast<SData*>(arrPtrData[i])) != NULL)
      { 
         int len = strlen(str);
         if( strncmp( str, ps->getData(), len) == 0)
         { 
            delete ps;
            arrPtrData[i] = NULL;
            --count;
            return true;
         }
      }
   return false;
}

int MyData::nextFreePos()      // Hilfsmethode: Liefert
{                              // n�chsten freien Index oder -1
   int i=iCur;
   do 
     if( arrPtrData[i] == NULL)
        return i;
     else 
        i = (i+1) % ARR_LENGTH;
   while( i != iCur);
   return -1;
}

bool MyData::insertX( double x)
{
   int i = nextFreePos();
   if( i < 0)
       return false;
   iCur = i;
   ++count;
   arrPtrData[i] = new XData(x);
   return true;
}

bool MyData::insertX()
{
   if( count == ARR_LENGTH)
   {   cout << "Kein freier Platz!" << endl;
       return false;
   }
   bool ok = true;
   double x = 0.0;
   cout << "Gleitpunktzahl eingeben: ";
   if( !(cin >> x))
   {  cout << "Ungueltige Eingabe!" << endl;
      cin.clear();
      ok = false;  
   }
   else
      ok = insertX(x);
   cin.ignore(256, '\n');  // Rest der Zeile ignorieren.
   return ok;
}

bool MyData::insertS(const char* s)
{
   int i = nextFreePos();
   if( i < 0)
       return false;
   iCur = i;
   if( strlen(s) > 0)
   {
     arrPtrData[i] = new SData(s);
     ++count;
     return true;
   }
   else
     return false;
}

bool MyData::insertS()
{
   if( count == ARR_LENGTH)
   {   cout << "Kein freier Platz!" << endl;
       return false;
   }
   bool ok = true;
   char buf[256];
   cout << "\nEine Zeile Text eingeben:" << endl;
   if( !cin.getline(buf, 256) || strlen(buf) == 0)
   {  cout << "Ungueltige Eingabe!" << endl;
      cin.clear();
      return false;  
   }
   else
      return insertS(buf);
}

void MyData::printData() const
{
   if( isEmpty())
   {  cout << "Keine Daten vorhanden!" << endl;
      return;
   }
   for( int i=0; i < ARR_LENGTH; ++i)
      if( arrPtrData[i] != NULL)
         cout << *arrPtrData[i] << endl;
}