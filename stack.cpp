#include "stack.h"

using namespace stack;

/****************************************************************/
bool stack::isEmpty(const Stack& s)
{
    return s == nullptr;
}

/****************************************************************/
void stack::push(const Elem x, Stack& s) 
{
    stackCell* c = new stackCell;
    c->elem = x;

    c->next = s;
    s = c;
}

/****************************************************************/
Elem stack::pop(Stack& s)
{
    if (isEmpty(s))
        return EMPTY_ELEM;
    
    stackCell* c = s;

    Elem e = s->elem;

    s = s->next;

    //delete c;

    return e;
}

/****************************************************************/

