#ifndef _FUN_MATRIX_OPERATOR_STACK_
#define _FUN_MATRIX_OPERATOR_STACK_

#include <stack>

enum Operations { SWAP,         //swap two rows
                  MULTIPLY,     //multiply a row by a scalar value
                  ADD};         //add a multiple of a row with another 
//extern purely because of the way I wanted to code this 
extern "C"
{
    typedef struct 
    {
        Operations type;

        //anonymous union containing the different possible operations
        union
        {
            //struct for swap operations
            struct
            {
                int source, dest;
            } Swap;

            //struct for multiplication operations
            struct
            {
                int row;
                double scalar;
            } Multiply;

            //struct for addition operations
            struct 
            {
                int src, dest;
                double srcScalar; 
            } Add;
        };   
    } OpNode;
}


class OpStack
{
    public:
        //no constructor 

        //returns a deep copy of the stack, for replaying operations
        OpStack * getCopy(void);
        
        OpNode * pop(void);

        void push(OpNode * entry);

        bool isEmpty(void);
        
        //for ease of use, constructors for each node type
        OpNode * SwapNode(int src,  int dest);
        OpNode * MultipleNode(int row, double scalar);
        OpNode * AddNode(int src, int dest, double srcScalar);

    protected:
        std::stack<OpNode *> opStack;
};

#endif /* _FUN_MATRIX_OPERATOR_STACK_ */
