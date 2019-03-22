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

bool isNumber (const string str) {
  for (int i=0; i<str.length(); i++) {
    if ( !std::isdigit(str[i]) )
      return false;
  }

  return true;
}

void printQueue (queue::Queue &codaToken) {
  queue::Elem e = queue::dequeue(codaToken);
  while(e != queue::EMPTY_ELEM) {
    printf("%d| %s\n", e->k, e->val.c_str());

    e = queue::dequeue(codaToken);
  }
}

// Estrae uno dopo l'altro i token dalla stringa "str", inserendoli via via nella coda "codaToken"
bool leggi(const string &str, queue::Queue &codaToken) {
  queue::createEmpty(codaToken);

  stringstream ss;
  ss << str;

  while (!ss.eof()) {
    string cToken;

    ss >> cToken;

    token *t = new token();
    t->val = cToken;

    if (cToken == "(")
      t->k = PARENTESI_APERTA;
    else if (cToken == ")")
      t->k = PARENTESI_CHIUSA;
    else if (cToken == "+")
      t->k = OP_SOMMA;
    else if (cToken == "-")
      t->k = OP_SOTTRAZIONE;
    else if (cToken == "*")
      t->k = OP_MOLTIPLICAZIONE;
    else {
      if (isNumber(cToken))
        t->k = NUMERO;
      else
        t->k = SCONOSCIUTO;
    }
    
    queue::enqueue(t, codaToken);
  }

  return true;
}

token* computeStack (stack::Stack codaToken) {
  token* chiusa = stack::pop(codaToken);
  //delete chiusa;

  token* op2Token = stack::pop(codaToken);
  token* opToken = stack::pop(codaToken);
  token* op1Token = stack::pop(codaToken);

  token* aperta = stack::pop(codaToken);
  //delete aperta;

  cout << chiusa->val << flush;
  cout << op2Token->val << flush;
  cout << opToken->val << flush;
  cout << op1Token->val << flush;
  cout << aperta->val << flush;

  int op2 = atoi(op2Token->val.c_str());
  int op1 = atoi(op1Token->val.c_str());

  int result = 0;

  if (opToken->k == OP_SOMMA)
    result = op1 + op2;
  else if (opToken->k == OP_SOTTRAZIONE)
    result = op1 - op2;
  else if (opToken->k == OP_MOLTIPLICAZIONE)
    result = op1 * op2;

  stack::Elem e = new token;
  e->k = NUMERO;
  e->val = to_string(result);

  //delete op2Token;
  //delete opToken;
  //delete op1Token;

  return e;
}

bool calcola(queue::Queue codaToken, int &risultato) {
  stack::Stack stackToken;

  while (stackToken != nullptr) {
    token* e = queue::dequeue(codaToken);

    stack::push(e, stackToken);

    if (e->k == PARENTESI_CHIUSA)
      computeStack(stackToken);

    stackToken = stackToken->next;
  }

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
