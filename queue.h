#include <iostream>
#include <stdexcept>

#include "token.h"
	
using namespace std;

// Implementa QUEUE 
namespace queue{


// Gli elementi della QUEUE sono token
typedef token token;

const token EMPTY_ELEM = { "", VUOTO };

struct queueCell {
  token token;
  queueCell* prev;
  queueCell* next;
};

typedef queueCell* Queue;

void createEmpty (Queue&);
bool isEmpty(const Queue&);
void enqueue(token, Queue&);  /* inserisce l'elemento alla fine della lista */
token dequeue(Queue&);        /* canqueueCella l'elemento in prima posizione (se esiste) e lo restituisce */
}
