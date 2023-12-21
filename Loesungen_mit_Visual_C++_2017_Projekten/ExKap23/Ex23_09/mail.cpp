// ---------------------------------------------------------
// mail.cpp
// Implementierung der Klassen
// Address, Mail, Letter, Parcel und NailService.
// ---------------------------------------------------------

#include "mail.h"

// -------------------------------------------------------
// Klasse Address

// Liest im Dialog eine neue Adresse ein.
bool Address::scan() 
{
    Address adr;                      // Puffer
    cout << "Nachname, Vorname:   ";
    getline( cin, adr.name);
    if( !cin  ||  adr.name == "")
       return false;
    cout << "Strasse mit Hausnr.: ";
    getline( cin, adr.street);
    if( !cin  ||  adr.street == "")
       return false;
    cout << "Postleitzahl Stadt:  ";
    getline( cin, adr.city);
    if( !cin  ||  adr.city == "")
       return false;
    cout << "Land:                ";
    getline( cin, adr.country);
    if( adr.country == "")
       adr.country = "Deutschland";
    *this = adr;                      // Adresse uebernehmen.
    return true;
}

ostream& Address::print( ostream& os) const
{
   os << '\t' << name << "\n\t" << street << "\n\t"
      << city << "\n\t" << country << endl;
   return os;
}

// -------------------------------------------------------
// Klasse Mail

ostream& Mail::print( ostream& os) const
{
   cout << "Mail-ID: " << id << endl;
   if( from.isValid())
      os << "Absender:\n" << from;
   else
      os << "Kein gueltiger Absender!" << endl;

   if( to.isValid())
      os << "Empfaenger:\n" << to;
   else
      os << "Kein gueltiger Empfaenger!" << endl;

   if( !delivered)
      os << "Post wurde noch nicht ausgeliefert!" << endl; 
   else
      os << "Post wurde an " << to.getName() << " ausgeliefert!"
         << endl;
   return os;
}

// -------------------------------------------------------
// Klasse Letter

ostream& Letter::print( ostream& os) const
{
   cout << "--- Brief-Daten ---\n"
        << "Kategorie: "
        << (ctg == STANDARD ? "Standard":"Express") << endl;
   Mail::print(os);
   return os;
}

// -------------------------------------------------------
// Klasse Parcel

ostream& Parcel::print( ostream& os) const
{
   cout << "--- Paket-Daten ---\n"
        << "Gewicht: " << weight << "  / "
        << (insured ? "Versichert.":"Nicht versichert.") << endl;
   Mail::print(os);
   return os;
}

// -------------------------------------------------------
// Klasse MailService

MailService::MailService() : iCurL(0), iCurP(0)
{
   for( int i=0; i < ARR_LENGTH; ++i)
      arrPtrLetter[i] = NULL,
      arrPtrParcel[i] = NULL;
}

MailService::~MailService()              // Destruktor
{
   for( int i=0; i < ARR_LENGTH; ++i)
      delete arrPtrLetter[i],
      delete arrPtrParcel[i];
}
                                         // Hilfsfunktion:
inline char getOneOf( char c1, char c2)  // Zeichen c1 oder c2 einlesen.
{                                        // Gross/Klein wird nicht 
   char c = 0;                           // unterschieden.
   while( cin && c != c1 && c != c2)
   {   cin >> c;  c = toupper(c); }
   cin.ignore(256,'\n');                 // Rest der Zeile ignorieren.
   return c;
}

bool MailService::newLetter()
{
   static unsigned long id = 10000;

   Letter *p = new Letter( ++id);
   cout << "Neuer Brief!\nAbsender:" << endl;
   p->scanFrom();
   cout << "Empfaenger:" << endl;
   if(! p->scanTo())
   {
      delete p;
      return false;
   }
   cout << "Standard- oder Express-Brief (S/E)? ";
   if( getOneOf( 'S','E') == 'E')
      p->setCategory( Letter::EXPRESS);

   arrPtrLetter[iCurL++] = p;
   return true;
}

bool MailService::newParcel()
{
   static unsigned long id = 20000;

   cout << "Neues Paket!\nGewicht: ";
   float w = 0.0;
   if( !(cin >> w))
      return false;
   cin.ignore(256,'\n');

   Parcel *p = new Parcel( ++id, w);
   cout << "Absender:" << endl;
   p->scanFrom();
   cout << "Empfaenger:" << endl;
   if( ! p->scanTo())
   {
      delete p;
      return false;
   }
   cout << "Paket versichern (J/N)? ";
   if( getOneOf( 'J','N') == 'J') 
      p->setInsured( true);

   arrPtrParcel[iCurP++] = p;
   return true;
}

void MailService::printLetters()
{
   if( iCurL == 0)
   {  cout << "Keine Briefe vorhanden!" << endl;
      return;
   }
   cout << "\n\t ***** Liste der Briefe: *****\n";
   for( int i=0; i < iCurL; ++i)
   {
      cout << *arrPtrLetter[i];
      cin.get();
   }
}

void MailService::printParcels()
{
   if( iCurP == 0)
   {  cout << "Keine Pakete vorhanden!" << endl;
      return;
   }
   cout << "  ***** Liste der Pakete: *****\n";
   int i;
   for( i=0; i < iCurP; ++i)
   {
      cout << *arrPtrParcel[i];
      cin.get();
   }
}

Letter* MailService::getLetter( unsigned long id) const
{
   for( int i=0; i < ARR_LENGTH; ++i)
      if( arrPtrLetter[i] != NULL &&
          arrPtrLetter[i]->getID() == id)
        return arrPtrLetter[i];       // Gefunden!
   return NULL;                       // Nicht gefunden.
}

Parcel* MailService::getParcel( unsigned long id) const
{
   for( int i=0; i < ARR_LENGTH; ++i)
      if( arrPtrParcel[i] != NULL &&
          arrPtrParcel[i]->getID() == id)
        return arrPtrParcel[i];       // Gefunden!
   return NULL;                       // Nicht gefunden.
}