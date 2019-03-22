#include "queue.h"

using namespace queue;


/****************************************************************/
/* 			FUNZIONI SULLE CODE 			*/
/****************************************************************/

/****************************************************************/
void queue::createEmpty(Queue& l) // aggiunge e in coda
{
   l = new queueCell;
   l->next = l;
   l->prev = l;
}

/****************************************************************/
void queue::enqueue(Elem e, Queue& l) // aggiunge e in coda
{
   queueCell* c = new queueCell;
   c->elem = e;

   c->next = l->next;
   c->prev = l;

   l->next->prev = c;
   l->next = c;
}


/****************************************************************/
Elem queue::dequeue(Queue& l) // rimuove il primo elemento e lo restituisce
{
   if (isEmpty(l))
      return EMPTY_ELEM;
   
   queueCell* c = l->prev;

   Elem e = c->elem;

   l->prev = c->prev;
   c->prev->next = l;

   delete c;

   return e;
}

/****************************************************************/
bool queue::isEmpty(const Queue& l)
{
  return l->next == l;
}

/****************************************************************/
