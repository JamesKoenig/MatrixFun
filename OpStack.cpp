#include <stdarg.h>
#include "OpStack.hpp"


//perform a deep copy
OpStack * OpStack::getCopy(void)
{
    //TODO finish
}

Node * OpStack::pop(void)
{
    Node * current;
    //TODO finish
}

void OpStack::push(Node * entry)
{
    //do stuff 
    //TODO finish
}


static Node * makeNode(Operations type, ...)
{
    va_list arg_p;
    Node * retVal = NULL;

    va_start(arg_p, type);
    //if we successfullly allocate the Node
    if(retVal = malloc(sizeof(Node)))
    {
        switch(retVal->Type = type)
        {
            //set it up if it's a swap node
            case SWAP:
                retVal->Swap.source = va_arg(arg_p, int);
                retVal->Swap.dest   = va_arg(arg_p, int);
                break;
            
            //set it up if it's a mutliplication node
            case MULTIPLY:
                retVal->Multiply.row    = va_arg(arg_p, int);
                retVal->Multiply.scalar = va_arg(arg_p, double);
                break;
            case ADD:
                retVal->Add.src       = va_arg(arg_p, int);
                retVal->Add.dest      = va_arg(arg_p, int);
                retVal->Add.srcScalar = va_arg(arg_p, double);
                break;
            //invalid type handle (probably will remove this)
            default:
                free(retVal);
                retVal = NULL;
                break; 
        }

    }

    va_end(arg_p);
    return retVal;
}


//returns NULL on a memory failure, a node address on success
Node * OpStack::SwapNode(int src, int dest) 
{
    return makeNode(SWAP, src, dest);
}

Node * OpStack::MultipleNode(int row, double scalar)
{
    return makeNode(MULTIPLY, row, scalar);
}

Node * OpStack::AddNode(int src, int dest, double srcScalar)
{
    return makeNode(ADD, src, dest, srcScalar);
}



