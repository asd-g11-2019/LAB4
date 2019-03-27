#include <cstddef> // serve per il NULL
#include <iostream>
#include <stdexcept>

#include "token.h"

using namespace std;

// Implementa STACK

namespace stack{

struct stackCell {
  token token;
  stackCell* next;
};

typedef stackCell* Stack;

const token EMPTY_ELEM = { "", VUOTO };
const token ERROR = { "", ERRORE };
const Stack EMPTY_STACK = nullptr;

bool isEmpty(const Stack&);
void push(const token, Stack&);	/* aggiunge elem in cima (operazione safe, si può sempre fare) */
token pop(Stack&);	/* toglie dallo stack l'ultimo elemento e lo restituisce; se lo stack è vuoto 
                           viene sollevata un'eccezione) */
}
