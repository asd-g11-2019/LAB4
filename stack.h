#include <cstddef> // serve per il NULL
#include <iostream>
#include <stdexcept>

#include "token.h"

using namespace std;

// Implementa STACK

namespace stack{

// Gli elementi dello STACK sono token
typedef token* Elem;

struct stackCell {
  Elem elem;
  stackCell* next;
};

typedef stackCell* Stack;

const Elem ERROR = nullptr;
const Elem EMPTY_ELEM = nullptr;
const Stack EMPTY_STACK = nullptr;

bool isEmpty(const Stack&);
void push(const Elem, Stack&);	/* aggiunge elem in cima (operazione safe, si può sempre fare) */
Elem pop(Stack&);	/* toglie dallo stack l'ultimo elemento e lo restituisce; se lo stack è vuoto 
                           viene sollevata un'eccezione) */
}
