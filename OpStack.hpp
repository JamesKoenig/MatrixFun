#ifndef _FUN_MATRIX_OPERATOR_STACK_
#define _FUN_MATRIX_OPERATOR_STACK_


enum Operations { SWAP,         //swap two rows
                  MULTIPLY,     //multiply a row by a scalar value
                  ADD};         //add a multiple of a row with another

//extern purely because of the way I wanted to code this 
extern "C"
{
    typedef struct Node_s
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

        //pointers to previous and next nodes
        struct Node_s * next;
    } Node;
}


class OpStack
{
    public:
        //no constructor 

        //returns a deep copy of the stack, for replaying operations
        OpStack * getCopy(void);
        
        Node * pop(void);

        void push(Node * entry);
        
        //for ease of use, constructors for each node type
        Node * SwapNode(int src,  int dest);
        Node * MultipleNode(int row, double scalar);
        Node * AddNode(int src, int dest, double srcScalar);

    protected:
        Node * stack;
}

#endif /* _FUN_MATRIX_OPERATOR_STACK_ */
