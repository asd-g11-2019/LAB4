/////////////////////////////////////////////////////////////////////
//
// Laboratorio 3: calcolo di semplici espressioni numeriche 
//                mediante pile e code
//
// vengono accettati dall'esterno solo numeri positivi.
// Per trattare anche numeri negativi occorre modificare
// l'analizzatore lessicale.
//
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "token.h"
#include "queue.h"
#include "stack.h"

using std::cout;
using std::cin;
using std::string;
using std::stringstream;
using std::istringstream;
using std::ostringstream;

/////////////////////////////////////////////////////////////////////
// Funzioni principali: leggi() e calcola()
/////////////////////////////////////////////////////////////////////

// Estrae uno dopo l'altro i token dalla stringa "str", inserendoli via via nella coda "codaToken"
bool leggi(const string &str, queue::Queue &codaToken) {
  queue::createEmpty(codaToken); // Creo una coda vuota

  stringstream ss; // Inizializzo uno stringstream
  ss << str; // Scrivo la striga nello stringsream

  while (!ss.eof()) { // Finche' non termina lo stringstream
    token *t = new token(); // Inizializzo il nuovo token

    if (!prossimoToken(ss, t)) // Se il token non e' valido
      return false; // Restituisco errore
    
    queue::enqueue(t, codaToken); // Inserisco il token nella queue
  }

  return true;
}

// Elabora gli ultimi 5 token inseriti nello stack
// e restituisce un token equivalente (il risultato sotto forma di numero)
// Nel nostro caso riconosciamo l'errore sintattico con stack::ERROR
token* computeStack (stack::Stack &stackToken) {
  token* chiusa = stack::pop(stackToken); // Ottengo il primo token
  if (chiusa->k != PARENTESI_CHIUSA) // Se non e' una parentesi chiusa
    return stack::ERROR; // Restituisco errore
  delete chiusa; // Elimino il token dalla memoria

  token* op2Token = stack::pop(stackToken); // Ottengo il secondo token
  if (op2Token->k != NUMERO) //Se non e' un numero
    return stack::ERROR; // Restituisco errore

  token* opToken = stack::pop(stackToken); // Ottengo il terzo token
  if (opToken->k != OP_SOMMA && opToken->k != OP_SOTTRAZIONE && opToken->k != OP_MOLTIPLICAZIONE) // Se non e' un'operazione
    return stack::ERROR; // Restituisco errore

  token* op1Token = stack::pop(stackToken); // Ottengo il quarto token
  if (op1Token->k != NUMERO) //Se non e' un numero
    return stack::ERROR; // Restituisco errore

  token* aperta = stack::pop(stackToken); // Ottengo il quinto token
  if (aperta->k != PARENTESI_APERTA)
    return stack::ERROR; // Restituisco errore
  delete aperta; // Elimino il token dalla memoria

  // Converto i due operandi in numeri interi
  int op2 = str2int(op2Token->val);
  int op1 = str2int(op1Token->val);

  int result = 0;

  switch (opToken->k) {
    case OP_SOMMA: // Se l'operazione e' una somma
      result = op1 + op2;
      break; // Effettuo la somma
    case OP_SOTTRAZIONE: // Se l'operazione e' una sottrazione
      result = op1 - op2; // Effettuo la sottrazione
      break;
    case OP_MOLTIPLICAZIONE: // Se l'operazione e' una moltiplicazione
      result = op1 * op2; // Effetuo la moltiplicazione
      break;
  }


  stack::Elem e = new token; // Preparo il nuovo token
  e->k = NUMERO; // Come numero
  e->val = int2str(result); // E come valore il risultato

  // Elimino i token dalla memoria
  delete op2Token;
  delete opToken;
  delete op1Token;

  return e; // Restituisco il nuovo token
}

bool calcola(queue::Queue codaToken, int &risultato) {
  stack::Stack stackToken = stack::EMPTY_STACK; // Inizializzo uno stack vuoto

  token* old; // Il penultimo token letto (servira' alla fine per controllare la validita')
  token* e = queue::dequeue(codaToken); // L'ultimo token letto

  while (e != stack::EMPTY_ELEM) { // Finche esiste un token nella coda
    stack::push(e, stackToken); // Inserisco il token nello stack

    if (e->k == PARENTESI_CHIUSA) { // Se e' una parentesi chiusa
      stack::Elem res = computeStack(stackToken); // Elaboro gli ulttimi 5 token dello stack

      if (res == stack::ERROR) // Se c'e' stato un errore
        return false; // Restituisco errore

      stack::push(res, stackToken); // Inserisco il risultato nello stack
    }

    old = e; // Metto da parte il token

    e = queue::dequeue(codaToken); // E passo al successivo
  }

  if (old->k != PARENTESI_CHIUSA) // Se l'ultimo token della cosa non e' una parentesi chiusa
    return false; // Restituisco errore

  stack::Elem result = stack::pop(stackToken); // Ottengo l'ultimo elemento rimasto nello stack
  risultato = str2int(result->val); // Lo converto in numero intero e lo assegno al risultato

  return true;
}

/////////////////////////////////////////////////////////////////////
//                               MAIN
/////////////////////////////////////////////////////////////////////

int main() {

  string s;
  queue::Queue q;
  int r;

  cout << "Inserisci l'espressione che vuoi valutare:" << endl;
  getline(cin,s);

  if (!leggi(s,q)) {
    cout << "errore lessicale\n";
    exit(1);
  }

  if (!calcola(q,r)) {
    cout << "errore sintattico\n";
    exit(1);
  }

  cout << "risultato: " << r << "\n";
  exit(0);
}
