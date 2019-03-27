#include "stack.h"

using namespace stack;

/****************************************************************/
/* 			FUNZIONI SULLE PILE 			*/
/****************************************************************/

// Come struttura base abbiamo scelto una lista semplice

/****************************************************************/
bool stack::isEmpty(const Stack &s)
{
  return s == EMPTY_STACK; // Se lo stack e' vuoto
}

/****************************************************************/
void stack::push(const token x, Stack &s) 
{
  stackCell* c = new stackCell; // Inizializzo la nuova cella
  c->token = x; // Imposto l'elemento

  // Ricostruisco i collegamenti
  c->next = s;
  s = c;
}

/****************************************************************/
token stack::pop(Stack &s)
{
  if (isEmpty(s)) // Se e' vuoto
    return EMPTY_ELEM; // Non esiste alcun elemento
  
  stackCell* c = s; // Ottengo la cella da rimuovere

  token e = s->token; // Ottengo l'elemento

  // Ricostruisco i collegamenti
  s = s->next;

  delete c; // Elimino la cella

  return e; // Restituisco l'elemento
}

/****************************************************************/

