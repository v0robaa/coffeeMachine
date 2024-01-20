#ifndef COFFEEMACHINE_OUTPUT_H
#define COFFEEMACHINE_OUTPUT_H
#include "cl_base.h"
using namespace std;

class Output : public cl_base
{
public:
    Output(cl_base* p_head, string name);
    void handler_print(string text);
};

#endif //COFFEEMACHINE_OUTPUT_H
