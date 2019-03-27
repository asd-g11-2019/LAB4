#include "queue.h"

using namespace queue;

/****************************************************************/
/* 			FUNZIONI SULLE CODE 			*/
/****************************************************************/

// Come struttura base abbiamo scelto una lista doppiamente collegata e circolare con sentinella

/****************************************************************/
void queue::createEmpty(Queue& l) // aggiunge e in coda
{
  l = new queueCell; // Inizializzo una nuova cella (sentinella)

  // Creo i collegamenti
  l->next = l;
  l->prev = l;
}

/****************************************************************/
void queue::enqueue(token e, Queue& l) // aggiunge e in coda
{
  queueCell* c = new queueCell; // Inizializzo una nuova cella
  c->token = e; // Imposto l'elemento

  // Ricostruisco i collegamenti
  c->next = l->next; 
  c->prev = l;

  l->next->prev = c;
  l->next = c;
}


/****************************************************************/
token queue::dequeue(Queue& l) // rimuove il primo elemento e lo restituisce
{
  if (isEmpty(l)) // Se e' vuoto
    return EMPTY_ELEM; // Non esiste alcun elemento
  
  queueCell* c = l->prev; // Ottengo l'ultima cella

  token e = c->token; // Ottengo l'elemento

  // Ricostruisco i collegamenti
  l->prev = c->prev;
  c->prev->next = l;

  delete c; // Elimino la cella

  return e; // Resituisco l'elemento
}

/****************************************************************/
bool queue::isEmpty(const Queue& l)
{
  return l->next == l; // Se esiste solo la sentinella
}

/****************************************************************/
