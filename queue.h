#include <iostream>
#include <stdexcept>

#include "token.h"
	
using namespace std;

// Implementa QUEUE 
namespace queue{


// Gli elementi della QUEUE sono token
typedef token* Elem;

const Elem EMPTY_ELEM = nullptr;

struct queueCell {
  Elem elem;
  queueCell* prev;
  queueCell* next;
};

typedef queueCell* Queue;

void createEmpty (Queue&);
bool isEmpty(const Queue&);
void enqueue(Elem, Queue&);  /* inserisce l'elemento alla fine della lista */
Elem dequeue(Queue&);        /* canqueueCella l'elemento in prima posizione (se esiste) e lo restituisce */
}
