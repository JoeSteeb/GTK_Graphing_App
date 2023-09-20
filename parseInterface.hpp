#ifndef PARSEINTERFACE_H_NAME
#define PARSEINTERFACE_H_NAME

#include <iostream>
#include <matheval.h>

class equation
{
    private:
        void *function;
    public:
        equation(char * buffer)
        {
            function = evaluator_create (buffer);
        }
        ~equation()
        {
            evaluator_destroy(function);
        }
        float evaluate(float x)
        {
            // printf("evalueated: %g\n", evaluator_evaluate_x (function, x));
            return evaluator_evaluate_x (function, x);
        }

};

#endif