/////////////////////////////////////////////////////////////////////
//
// Laboratorio 3: calcolo di semplici espressioni numeriche 
//                mediante pile e code
//
// vengono accettati dall'esterno solo numeri positivi.
// Per trattare anche numeri negativi occorre modificare
// l'analizzatore lessicale.
//
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "token.h"

using std::cout;
using std::cin;
using std::string;
using std::stringstream;
using std::istringstream;
using std::ostringstream;

/////////////////////////////////////////////////////////////////////
// Funzioni ausiliarie su tipi di dato semplici
/////////////////////////////////////////////////////////////////////

// Controllo se str e' un numero
bool isNumber (const string str) {
  for (int i=0; i<str.length(); i++) // Per ogni carattere di str
    if ( !std::isdigit(str[i]) ) // Se non e' una cifra
      return false; // Restituisco false

  return true;
}

// da stringa a numero
int str2int(const string &s) {
  return atoi(s.c_str());
}

// da numero a stringa
string int2str(int n) {
  return std::to_string(n);
}

// ritorna false se e solo se token di tipo sconosciuto o se stringa vuota.
// se stringa non vuota, la stringa perde il pezzo iniziale,
// che diventa token.

bool prossimoToken(string &s, token &t) {
  if (s.length() == 0) // Se il token ha una lunghezza = 0 (ovvero ci sono 2 spazi attaccati)
    return false; // Restituico errore

  t.val = s; // Imposto il valore del token

  // Imposto il tipo di token
  if (s == "(")
    t.k = PARENTESI_APERTA;
  else if (s == ")")
    t.k = PARENTESI_CHIUSA;
  else if (s == "+")
    t.k = OP_SOMMA;
  else if (s == "-")
    t.k = OP_SOTTRAZIONE;
  else if (s == "*")
    t.k = OP_MOLTIPLICAZIONE;
  else { // Se non e' un token "facilemente riconoscibile"
    if (isNumber(s)) // Controllo se e' un numero
      t.k = NUMERO;
    else // Se non lo e'
      return false; // Restituisco errore
  }

  return true;
}
