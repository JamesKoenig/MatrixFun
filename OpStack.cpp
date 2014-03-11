#include <cstdarg>
#include <cstdlib>
#include "OpStack.hpp"


//perform a deep copy of the stack and return the new stack
OpStack * OpStack::getCopy(void)
{
    //TODO finish
    //Seriously
    return NULL;
}

//pops an element off the stack
OpNode * OpStack::pop(void)
{
    OpNode * cur;
    if(opStack.empty())
        return NULL;
    else
    {
        cur = opStack.top();
        opStack.pop();
        return cur;
    }
}

void OpStack::push(OpNode * entry)
{
    if(entry)
        opStack.push(entry);
    return;
}

bool OpStack::isEmpty(void)
{
    return opStack.empty();
}


static OpNode * makeNode(Operations type, ... )
{
    va_list arg_p;
    OpNode * retVal = NULL;

    va_start(arg_p, type);
    //if we successfullly allocate the Node
    if(retVal = (OpNode *) malloc(sizeof(OpNode)))
    {
        switch(retVal->type = type)
        {
            //set it up if it's a swap node
            case SWAP:
                retVal->Swap.source = va_arg(arg_p, int);
                retVal->Swap.dest   = va_arg(arg_p, int);
                break;
            
            //set it up if it's a mutliplication node
            case MULTIPLY: retVal->Multiply.row    = va_arg(arg_p, int); retVal->Multiply.scalar = va_arg(arg_p, double);
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
OpNode * OpStack::SwapNode(int src, int dest) 
{
    return makeNode(SWAP, src, dest);
}

OpNode * OpStack::MultipleNode(int row, double scalar)
{
    return makeNode(MULTIPLY, row, scalar);
}

OpNode * OpStack::AddNode(int src, int dest, double srcScalar)
{
    return makeNode(ADD, src, dest, srcScalar);
}

/* test code */
#ifdef _OPSTACK_TEST_CODE_COMPILE_

#include <stdio.h>

//WARNING: calls free on the node it was passed
void printNode(OpNode * node)
{
    switch(node->type)
    {
        case SWAP:
            printf("\tswap operation\n\t\tfrom row %d\n\t\tto row %d\n", 
                    node->Swap.source, node->Swap.dest);
            break;
        case MULTIPLY:
            printf("\tmultiply operation\n\t\ton row %d\n\t\tby %lf\n",
                    node->Multiply.row, node->Multiply.scalar);
            break;
        case ADD:
            printf("\tadd operation\n\t%lf times row %d\n\t\tadded to row %d\n",
                    node->Add.srcScalar, node->Add.src, node->Add.dest);
            break;
    }
    putchar('\n');
    //because there is no other opportunity to do this
    free(node);
    return;
}

void printStack(OpStack Stack)
{
    printf("dumping stack...\n");
    while(!Stack.isEmpty())
    {
        printNode(Stack.pop());
    }
}

int main(int argc, char ** argv)
{
    OpStack stackum;
    
    /* the following are the operations to reduce the matrix:
     * 0 1 2
     * 0 1 1 
     * 1 0 2 
     */

    stackum.push(stackum.SwapNode(1,3));

    /* matrix is now
     * 1 0 2
     * 0 1 1 
     * 0 1 2 
     */
    stackum.push(stackum.AddNode(2,3,-1.0));

    /* matrix is now 
     * 1 0 2 
     * 0 1 1 
     * 0 0 1
     */
    stackum.push(stackum.AddNode(3,1,-2.0));

    /* matrix is now
     * 1 0 0
     * 0 1 1 
     * 0 0 1
     */
    stackum.push(stackum.AddNode(3,2,-1.0));

    /* and we have the 3x3 identity matrix! Woo */

    //TODO add a use of the stack deep copy function here
    printStack(stackum);

    return 0;
}


#endif /* _OPSTACK_TEST_CODE_COMPILE_ */


